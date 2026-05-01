/* SPDX-License-Identifier: BSD-2-Clause */

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

#include "common.h"

#define USAGE	"Usage: %s [-n] [rlimit]..."

static struct {
	int value;
	const char *name;
} rlimits[] = {
#include "rlimits.h"
};

static int nflag;

static const char *
strlimit(rlim_t rlim, char *buf, size_t bufsize)
{
	if (rlim == RLIM_INFINITY)
		return ("infinity");

	snprintf(buf, bufsize, "%llu", (unsigned long long) rlim);
	return (buf);
}

static void
print(int value, const char *name)
{
	char cur[32], max[32];
	struct rlimit rl;

	if (nflag) {
		printf("%s\n", name);
		return;
	}

	if (getrlimit(value, &rl) < 0)
		err(1, "getrlimit: %s", name);

	printf("%-20s\t%12s\t%12s\n", name,
	    strlimit(rl.rlim_cur, cur, sizeof(cur)),
	    strlimit(rl.rlim_max, max, sizeof(max)));
}

int
main(int argc, char *argv[])
{
	int i, n, ch, value;

	while ((ch = getopt(argc, argv, "n")) != -1) {
		switch (ch) {
		case 'n':
			nflag = 1;
			break;
		default:
			errx(1, USAGE, getprogname());
		}
	}

	argv += optind;

	if (*argv == NULL) {
		for (i = 0; i < nitems(rlimits); i++)
			print(rlimits[i].value, rlimits[i].name);
		return (0);
	}

	for (; *argv != NULL; argv++) {
		if ((value = xatoi(*argv)) >= 0) {
			for (i = 0; i < nitems(rlimits); i++)
				if (rlimits[i].value == value) {
					print(value, rlimits[i].name);
					break;
				}
			if (i == nitems(rlimits))
				errx(1, "Unknown rlimit code: %s", *argv);
		} else {
			n = strncmp(*argv, "RLIMIT_", 7) ? 7 : 0;
			for (i = 0; i < nitems(rlimits); i++)
				if (strcmp(*argv, rlimits[i].name + n) == 0) {
					print(rlimits[i].value, rlimits[i].name);
					break;
				}
			if (i == nitems(rlimits))
				errx(1, "Unknown rlimit name: %s", *argv);
		}
	}

	return (0);
}
