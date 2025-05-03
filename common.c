#include <stdlib.h>
#include <errno.h>

#include "common.h"

int
xatoi(const char *str)
{
	char *endptr;
	int value;

	errno = 0;
	value = (int) strtoul(str, &endptr, 10);
	if (errno || *endptr != '\0')
		return (-1);

	return (value);
}
