/* SPDX-License-Identifier: BSD-2-Clause */

#ifdef __linux__
extern char *__progname;
#define getprogname()   (__progname)
#endif

#undef nitems
#define nitems(arr)     ((int)((sizeof((arr)) / sizeof((arr)[0]))))

/* Make strerror() & strsignal() return const char * */
#define XSTRFUNC(func)	\
static const char *	\
x##func(int n)		\
{			\
	const char *s;	\
	s = func(n);	\
	return (s);	\
}

int xatoi(const char *str);
