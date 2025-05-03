#ifdef __linux__
extern char *__progname;
#define getprogname()   (__progname)
#endif

#undef nitems
#define nitems(arr)     ((int)((sizeof((arr)) / sizeof((arr)[0]))))

int xatoi(const char *str);
