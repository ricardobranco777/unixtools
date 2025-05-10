/* SPDX-License-Identifier: BSD-2-Clause */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <err.h>

#include "common.h"

#ifndef NSIG_MAX
#if defined(NSIG)
#define NSIG_MAX NSIG
#elif defined(_NSIG)
#define NSIG_MAX _NSIG
#endif
#endif

#define USAGE_STRERROR		"%s [-n] [errno]..."
#define USAGE_STRSIGNAL		"%s [-n] [[SIG]name]... [signum]..."
#define USAGE_GAI_STRERROR	"%s [-n] [errcode]..."

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

static struct entry gerrlist[] = {
#include "gerrnos.h"
};

typedef const char *(*strfunc_t)(int);
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

/* Make strerror() & strsignal() return const char* */
#define XSTRFUNC(func)	\
static const char *	\
x##func(int n)		\
{			\
	const char *s;	\
	s = func(n);	\
	return (s);	\
}

XSTRFUNC(strerror)
XSTRFUNC(strsignal)

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
getmax(struct entry *list, int items)
{
	int i, max = 0;
#ifdef ELAST
	if (strfunc == xstrerror)
		return (ELAST);
#endif
#ifdef NSIG_MAX
	if (strfunc == xstrsignal)
		return (NSIG_MAX - 1);
#endif
#ifdef EAI_MAX
	if (strfunc == xgai_strerror)
		return (EAI_MAX);
#endif
	for (i = 0; i < items; i++)
		if (abs(list[i].value) > max)
			max = abs(list[i].value);
	return max;
}

int
main(int argc, char *argv[])
{
	int i, n, items, value;
	struct entry *list;
	const char *usage;
	const char *str;
	int ch;

	const char *progname = getprogname();
	if (!strncmp(progname, "strerror", sizeof("strerror") - 1)) {
		list = errlist;
		items = nitems(errlist);
		usage = USAGE_STRERROR;
		strfunc = xstrerror;
	} else if (!strncmp(progname, "strsignal", sizeof("strsignal") - 1)) {
		list = siglist;
		items = nitems(siglist);
		usage = USAGE_STRSIGNAL;
		strfunc = xstrsignal;
	} else if (!strncmp(progname, "gai_strerror", sizeof("gai_strerror") - 1)) {
		list = gerrlist;
		items = nitems(gerrlist);
		usage = USAGE_GAI_STRERROR;
		strfunc = xgai_strerror;
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
			for (i = 0, str = NULL; i < items; i++)
				if (abs(list[i].value) == value) {
					if ((str = strfunc(value)) == NULL)
						break;
					print(value, list[i].name, str);
					if (nflag)
						break;
				}
		} else {
			if (strfunc == xstrsignal)
				n = strncmp(*argv, "SIG", 3) ? 3 : 0;
			else if (strfunc == xgai_strerror)
				n = strncmp(*argv, "EAI_", 4) ? 4 : 0;
			else
				n = 0;
			for (i = 0, str = NULL; i < items; i++)
				if (strcmp(*argv, list[i].name + n) == 0) {
					value = list[i].value;
					if ((str = strfunc(value)) != NULL)
						print(value, list[i].name, str);
					break;
				}
		}
		if (str == NULL)
			errx(1, "Unknown: %s", *argv);
	}

	return (0);
}
