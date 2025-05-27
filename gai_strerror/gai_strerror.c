/* SPDX-License-Identifier: BSD-2-Clause */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <netdb.h>

#include "common.h"

#define USAGE	"Usage: %s [-n] [[EAI_]name]... [number]..."

struct entry {
	int value;
	const char *name;
};

static struct entry list[] = {
#include "gerrnos.h"
};

static int nflag;

static void
print(int value, const char *name, const char *str)
{
	if (nflag)
		printf("%s\n", str);
	else
		printf("%d\t%-20s %s\n", value, name, str);
}

/* Make gai_strerror() support positive integers */
static const char *
xgai_strerror(int n)
{
#ifndef EAI_MAX
	n = -abs(n);
#endif
	return gai_strerror(n);
}

static int
getmax(void)
{
#ifdef EAI_MAX
	return (EAI_MAX);
#else
	int i, max = 0;

	for (i = 0; i < nitems(list); i++)
		if (abs(list[i].value) > max)
			max = abs(list[i].value);

	return (max);
#endif
}

int
main(int argc, char *argv[])
{
	const char *str;
	int ch, i, n, value;

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
		for (value = 1; value <= getmax(); value++) {
			str = xgai_strerror(value);
			for (i = 0; i < nitems(list); i++)
				if (abs(list[i].value) == value) {
					print(value, list[i].name, str);
					if (nflag)
						break;
				}
		}
		return (0);
	}

	for (; *argv != NULL; argv++) {
		if ((value = xatoi(*argv)) > 0) {
			for (i = 0, str = NULL; i < nitems(list); i++)
				if (abs(list[i].value) == value) {
					if ((str = xgai_strerror(value)) == NULL)
						break;
					print(value, list[i].name, str);
					if (nflag)
						break;
				}
		} else {
			n = strncmp(*argv, "EAI_", 4) ? 4 : 0;
			for (i = 0, str = NULL; i < nitems(list); i++)
				if (strcmp(*argv, list[i].name + n) == 0) {
					value = list[i].value;
					if ((str = xgai_strerror(value)) != NULL)
						print(value, list[i].name, str);
					break;
				}
		}
		if (str == NULL)
			errx(1, "Unknown: %s", *argv);
	}

	return (0);
}
