/* SPDX-License-Identifier: BSD-2-Clause */

#ifdef __linux__
extern char *__progname;
#define getprogname()   (__progname)
#endif

#undef nitems
#define nitems(arr)     ((int)((sizeof((arr)) / sizeof((arr)[0]))))

/* https://man.openbsd.org/strlcpy.3 */
#if defined(__GLIBC__) && (__GLIBC__ < 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ < 38))
#define strlcpy(dst, src, len)	snprintf(dst, len, "%s", src)
#endif

int xatoi(const char *str);
