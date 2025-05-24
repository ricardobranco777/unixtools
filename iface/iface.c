/* SPDX-License-Identifier: BSD-2-Clause */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

#include "common.h"

#define USAGE	"Usage: %s [-4|-6] TARGET"

#define PORT	60000

union sockaddr_union {
	struct sockaddr_in v4;
	struct sockaddr_in6 v6;
};

static const char *
get_iface(const struct ifaddrs *ifaddr, int family, union sockaddr_union *src)
{
	const struct ifaddrs *ifa;
	struct sockaddr_in6 *addr6;
	struct sockaddr_in *addr4;

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != family)
			continue;
		if (family == AF_INET) {
			addr4 = (struct sockaddr_in *)ifa->ifa_addr;
			if (memcmp(&addr4->sin_addr, &src->v4.sin_addr,
			    sizeof(struct in_addr)) == 0)
				return ifa->ifa_name;
		} else if (family == AF_INET6) {
			addr6 = (struct sockaddr_in6 *)ifa->ifa_addr;
			if (memcmp(&addr6->sin6_addr, &src->v6.sin6_addr,
			    sizeof(struct in6_addr)) == 0)
				return ifa->ifa_name;
		}
	}

	return "unknown";
}

int
main(int argc, char *argv[])
{
	char src_addr[INET6_ADDRSTRLEN];
	char dst_addr[INET6_ADDRSTRLEN];
	struct addrinfo hints, *res, *ai;
	union sockaddr_union src, dst;
	struct ifaddrs *ifaddr;
	const char *ifname;
	int family = AF_UNSPEC;
	socklen_t namelen;
	int ch, error, s;

	while ((ch = getopt(argc, argv, "46")) != -1) {
		switch (ch) {
		case '4':
			family = AF_INET;
			break;
		case '6':
			family = AF_INET6;
			break;
		default:
			errx(1, USAGE, getprogname());
		}
	}

	argc -= optind;
	argv += optind;
	if (argc != 1)
		errx(1, USAGE, getprogname());

	(void)memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_DGRAM;

	if ((error = getaddrinfo(*argv, NULL, &hints, &res)) != 0)
		errx(1, "getaddrinfo: %s: %s", *argv, gai_strerror(error));

	if (getifaddrs(&ifaddr) == -1)
		err(1, "getifaddrs");

	for (ai = res; ai != NULL; ai = ai->ai_next) {
		(void)memset(&dst, 0, sizeof(dst));
		(void)memcpy(&dst, ai->ai_addr, ai->ai_addrlen);
		if (ai->ai_family == AF_INET)
			dst.v4.sin_port = htons(PORT);
		else if (ai->ai_family == AF_INET6)
			dst.v6.sin6_port = htons(PORT);
		else
			continue;

		if ((s = socket(ai->ai_family, SOCK_DGRAM, 0)) == -1)
			err(1, "socket");
		if (connect(s, (struct sockaddr *)&dst, ai->ai_addrlen) == -1) {
			if (errno == EHOSTUNREACH || errno == ENETUNREACH) {
				(void)close(s);
				continue;
			} else
				err(1, "connect");
		}

		namelen = ai->ai_addrlen;
		if (getsockname(s, (struct sockaddr *)&src, &namelen) == -1)
			err(1, "getsockname");
		(void)close(s);

		if (inet_ntop(ai->ai_family, ai->ai_family == AF_INET
		    ? (void *)&dst.v4.sin_addr
		    : (void *)&dst.v6.sin6_addr,
		    dst_addr, sizeof(dst_addr)) == NULL)
			err(1, "inet_ntop");

		if (inet_ntop(ai->ai_family, ai->ai_family == AF_INET
		    ? (void *)&src.v4.sin_addr
		    : (void *)&src.v6.sin6_addr,
		    src_addr, sizeof(src_addr)) == NULL)
			err(1, "inet_ntop");

		ifname = get_iface(ifaddr, ai->ai_family, &src);
		printf("%s %s via %s %s\n", *argv, dst_addr, ifname, src_addr);
	}

	freeifaddrs(ifaddr);
	freeaddrinfo(res);
	return (0);
}
