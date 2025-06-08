/* SPDX-License-Identifier: BSD-2-Clause */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define __EXTENSIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "common.h"

#define USAGE	"Usage: %s [-n] [pathname] [[_PC_]name]..."

static struct {
	int value;
	const char *name;
} list[] = {
#include "pathconfs.h"
};

static char *path = NULL;
static int nflag;

static void
print(int index)
{
	const char *name = list[index].name;
	int value = list[index].value;
	char *str;
	long val;
	int ret;

	errno = ret = 0;
	if ((val = pathconf((path != NULL) ? path : ".", value)) == -1)
		str = strdup((errno == EINVAL) ? "invalid" : "");
	else
		ret = asprintf(&str, "%ld", val);
	if (str == NULL || ret == -1)
		err(1, "malloc");

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
	if (*argv != NULL && (strchr(*argv, '/') != NULL || *argv[0] == '.'))
		path = *argv++;

	if (*argv == NULL) {
		for (i = 0; i < nitems(list); i++)
			print(i);
		return (0);
	}

	for (; *argv != NULL; argv++) {
		n = strncmp(*argv, "_PC_", 4) ? 4 : 0;
		for (i = 0; i < nitems(list); i++)
			if (strcmp(*argv, list[i].name + n) == 0) {
				print(i);
				break;
			}
	}

	return (0);
}
