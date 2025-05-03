/* SPDX-License-Identifier: BSD-2-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "common.h"

#if !defined(NSIG) && defined(_NSIG)
#define NSIG	_NSIG
#endif

#define USAGE_STRERROR	"%s [-n] [errno]..."
#define USAGE_STRSIGNAL	"%s [-n] [[SIG]name]... [signum]..."

struct entry {
	int value;
	const char *name;
};

static struct entry errlist[] = {
#include "errnos.h"
};

static struct entry siglist[] = {
#include "signos.h"
};

typedef char *(*strfunc_t)(int);
static strfunc_t strfunc;

static int nflag;

static void
print(int value, const char *name, const char *str)
{
	if (nflag)
		printf("%s\n", str);
	else
		printf("%d\t%-20s %s\n", value, name, str);
}

static int
getmax(struct entry *list, int items)
{
	int i, max = 0;
#ifdef ELAST
	if (strfunc == strerror)
		return (ELAST);
#endif
#ifdef NSIG
	if (strfunc == strsignal)
		return (NSIG - 1);
#endif
	for (i = 0; i < items; i++)
		if (list[i].value > max)
			max = list[i].value;
	return max;
}

int
main(int argc, char *argv[])
{
	int i, n, items, value;
	struct entry *list;
	const char *usage;
	char *str;
	int ch;

	const char *progname = getprogname();
	if (!strncmp(progname, "strerror", sizeof("strerror") - 1)) {
		list = errlist;
		items = nitems(errlist);
		usage = USAGE_STRERROR;
		strfunc = strerror;
	} else if (!strncmp(progname, "strsignal", sizeof("strsignal") - 1)) {
		list = siglist;
		items = nitems(siglist);
		usage = USAGE_STRSIGNAL;
		strfunc = strsignal;
	} else
		errx(1, "unknown program");

	while ((ch = getopt(argc, argv, "n")) != -1) {
		switch (ch) {
		case 'n':
			nflag = 1;
			break;
		default:
			errx(1, usage, progname);
		}
	}

	argv += optind;

	if (*argv == NULL) {
		for (value = 1; value <= getmax(list, items); value++) {
			str = strfunc(value);
			for (i = 0; i < items; i++)
				if (list[i].value == value) {
					print(value, list[i].name, str);
					if (nflag)
						break;
				}
		}
		return (0);
	}

	for (; *argv != NULL; argv++) {
		if ((value = xatoi(*argv)) > 0) {
			for (i = 0, str = NULL; i < items; i++)
				if (list[i].value == value) {
					if ((str = strfunc(value)) == NULL)
						break;
					print(value, list[i].name, str);
					if (nflag)
						break;
				}
		} else {
			n = (strfunc == strsignal && strncmp(*argv, "SIG", 3)) ? 3 : 0;
			for (i = 0, str = NULL; i < items; i++)
				if (strcmp(*argv, list[i].name + n) == 0) {
					value = list[i].value;
					if ((str = strfunc(value)) != NULL)
						print(value, list[i].name, str);
					break;
				}
		}
		if (str == NULL)
			errx(1, "Unknown %s: %s", progname + 3, *argv);
	}

	return (0);
}
