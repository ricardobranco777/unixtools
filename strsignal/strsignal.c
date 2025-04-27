#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#ifdef __linux__
extern char *__progname;
#define getprogname()   (__progname)
#endif

#define ISDIGIT(c)	((int)(c) >= '0' && ((int)(c) <= '9'))

#define USAGE	"%s [-n] [-q] [[SIG]name]... [signum]..."

static struct {
	int value;
	const char *str;
} list[] = {
#include "signos.h"
	{ -1, NULL }
};

#define FMTSTR  "%4d   %-20s %s\n"

int
main(int argc, char *argv[])
{
	int i, j, n, max;
	int value;
	int ch;
	int nflag, qflag;
	char *s, *endptr;

	nflag = qflag = 0;

	while ((ch = getopt(argc, argv, "nq")) != -1) {
		switch (ch) {
		case 'n':
			nflag = 1;
			break;
		case 'q':
			qflag = 1;
			break;
		default:
			errx(1, USAGE, getprogname());
		}
	}

	if (argc == optind) {
		max = 0;
		for (i = 0; list[i].str != NULL; i++)
			if (list[i].value > max)
				max = list[i].value;
		for (i = 1; i <= max; i++) {
			if ((s = strsignal(i)) == NULL)
				continue;
			for (j = 0; list[j].str != NULL; j++) {
				if (list[j].value == i) {
					if (nflag) {
						printf("%s\n", s);
						break;
					} else
						printf(FMTSTR, i, list[j].str, s);
				}
			}
		}
	}

	for (i = optind; i < argc; i++) {
		if (ISDIGIT(argv[i][0])) {
			errno = 0;
			value = (int) strtoul(argv[i], &endptr, 10);
			if (errno || *endptr != '\0')
				errx(1, "Invalid number: %s", argv[i]);
			for (j = 0, s = NULL; list[j].str != NULL; j++) {
				if (list[j].value == value) {
					if ((s = strsignal(value)) == NULL)
						break;
					if (nflag) {
						printf("%s\n", s);
						break;
					} else
						printf(FMTSTR, value, list[j].str, s);
				}
			}
		} else {
			for (j = 0, s = NULL; list[j].str != NULL; j++) {
				n = (strncmp(argv[i], "SIG", 3) != 0) ? 3 : 0;
				if (strcmp(argv[i], list[j].str + n) == 0) {
					value = list[j].value;
					if ((s = strsignal(value)) != NULL) {
						if (nflag)
							printf("%s\n", s);
						else
							printf(FMTSTR, value, list[j].str, s);
					}
					break;
				}
			}
		}
		if (s == NULL && !qflag)
			errx(1, "Unknown signal: %s", argv[i]);
	}

	return 0;
}
