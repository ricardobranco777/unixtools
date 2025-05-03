/* SPDX-License-Identifier: BSD-2-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <sysexits.h>

#include "common.h"

#define USAGE	"%s [-n] [exitcode]..."

static struct {
	int value;
	const char *name;
} exits[] = {
#include "exits.h"
};

static int nflag;

static void
print(int value, const char *name)
{
	if (nflag)
		printf("%s\n", name);
	else
		printf("%d\t%s\n", value, name);
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
		for (i = 0; i < nitems(exits); i++)
			print(exits[i].value, exits[i].name);
		return (0);
	}

	for (; *argv != NULL; argv++) {
		if ((value = xatoi(*argv)) >= 0) {
			for (i = 0; i < nitems(exits); i++) {
				if (exits[i].value == value) {
					print(value, exits[i].name);
					break;
				}
			}
			if (i == nitems(exits))
				errx(1, "Unknown exit code: %s", *argv);
		} else {
			n = strncmp(*argv, "EX_", 3) ? 3 : 0;
			for (i = 0; i < nitems(exits); i++) {
				if (strcmp(*argv, exits[i].name + n) == 0) {
					print(exits[i].value, exits[i].name);
					break;
				}
			}
			if (i == nitems(exits))
				errx(1, "Unknown exit name: %s", *argv);
		}
	}

	return (0);
}
