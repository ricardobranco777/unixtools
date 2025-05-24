/* SPDX-License-Identifier: BSD-2-Clause */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#if defined(__linux__)
#include <netinet/ether.h>
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__APPLE__)
#include <net/ethernet.h>
#define	ether_addr_octet octet
#elif defined(__sun__)
#include <sys/ethernet.h>
#include <sys/sockio.h>
#elif defined(__NetBSD__)
#include <net/if_ether.h>
#elif defined(__OpenBSD__)
#include <netinet/if_ether.h>
#else
#error not supported
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <getopt.h>

#include "common.h"

#define USAGE "Usage: %s [-i interface] [-P port] [-p password] lladdr..."

static in_addr_t
get_broadcast_address(const char *ifname)
{
	struct ifreq ifr;
	int sock;

	if (ifname == NULL || ifname[0] == '\0')
		return INADDR_BROADCAST;

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		err(1, "socket");

	(void)memset(&ifr, 0, sizeof(ifr));
	(void)strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

	if (ioctl(sock, SIOCGIFBRDADDR, &ifr) == -1)
		err(1, "ioctl: %s", ifname);

	(void)close(sock);
	return ((struct sockaddr_in *)&ifr.ifr_broadaddr)->sin_addr.s_addr;
}

static uint8_t *
get_password(const char *str)
{
	static uint8_t password[6];
	unsigned int values[6];
	int i;

	if (sscanf(str, "%2x:%2x:%2x:%2x:%2x:%2x",
	   &values[0], &values[1], &values[2],
	   &values[3], &values[4], &values[5]) != 6)
		return NULL;

	for (i = 0; i < 6; i++)
		password[i] = (uint8_t)values[i];

	return password;
}

static void
wake(struct ether_addr *mac, struct sockaddr_in sin, const uint8_t *password)
{
	uint8_t data[102 + 6];
	size_t size;
	int on = 1;
	int s;

	memset(data, 0xFF, 6);
	for (size = 6; size < sizeof(data); size += 6)
		(void)memcpy(data + size, mac->ether_addr_octet, 6);

	if (password != NULL) {
		(void)memcpy(data + 102, password, 6);
		size += 6;
	}

	if ((s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
		err(1, "socket");

	if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof(int)) == -1)
		err(1, "setsockopt");

	printf("Sending to %s via %s\n",
	    ether_ntoa(mac), inet_ntoa(sin.sin_addr));

	if (sendto(s, data, size, 0, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		err(1, "sendto");

	(void)close(s);
}

int
main(int argc, char *argv[])
{
	char ifname[IF_NAMESIZE] = {0};
	struct ether_addr ea, *mac;
	uint8_t *password = NULL;
	struct sockaddr_in sin;
	int port = 9;
	int i, ch;

	while ((ch = getopt(argc, argv, "i:P:p:")) != -1) {
		switch (ch) {
		case 'i':
			(void)strlcpy(ifname, optarg, sizeof(ifname));
			break;
		case 'P':
			port = xatoi(optarg); 
			if (port < 0 || port > 65535)
				errx(1, "Invalid port: %s", optarg);
			break;
		case 'p':
			if ((password = get_password(optarg)) == NULL)
				errx(1, "Invalid SecureOn password: %s", optarg);
			break;
		default:
			errx(1, USAGE, getprogname());
		}
	}

	if (optind >= argc)
		errx(1, USAGE, getprogname());

	(void)memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((uint16_t)port);
	sin.sin_addr.s_addr = get_broadcast_address(ifname);

	for (i = optind; i < argc; i++) {
		if ((mac = ether_aton(argv[i])) == NULL) {
			if (ether_hostton(argv[i], &ea) != 0)
				errx(1, "Missing in /etc/ethers: %s", argv[i]);
			mac = &ea;
		}

		wake(mac, sin, password);
	}

	return (0);
}
