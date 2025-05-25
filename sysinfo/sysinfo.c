/* SPDX-License-Identifier: BSD-2-Clause */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define __EXTENSIONS__

#ifdef sun
#include <sys/systeminfo.h>
#define HAVE_SYSINFO
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "common.h"

#define USAGE	"Usage: %s [-n] [[SI_]name]..."

static struct {
	int value;
	const char *name;
} list[] = {
#include "sysinfos.h"
};

static int nflag;

static void
print(int index)
{
	const char *name = list[index].name;
	int value = list[index].value;
	char dummy[2];
	char *str;
	int siz;

	if ((siz = sysinfo(value, dummy, sizeof(dummy))) == -1)
		err(1, "%s", name);
	if ((str = malloc(siz)) == NULL)
		err(1, "malloc");

	(void)sysinfo(value, str, siz);

	if (nflag)
		printf("%s\n", str);
	else
		printf("%-40s %s\n", name, str);

	free(str);
}

int
main(int argc, char *argv[])
{
	int ch, i, n;

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
		for (i = 0; i < nitems(list); i++)
			print(i);
		return (0);
	}

	for (; *argv != NULL; argv++) {
		n = strncmp(*argv, "SI_", 3) ? 3 : 0;
		for (i = 0; i < nitems(list); i++)
			if (strcmp(*argv, list[i].name + n) == 0) {
				print(i);
				break;
			}
	}

	return (0);
}
