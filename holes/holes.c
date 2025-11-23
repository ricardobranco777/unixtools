/* SPDX-License-Identifier: BSD-2-Clause */

#define _GNU_SOURCE
#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "common.h"

#define USAGE	"Usage: %s FILE"

#define print(t, m, n)	printf("%s from %jd to %jd length %jd\n", #t, (intmax_t)(m), (intmax_t)(n), (intmax_t)(n - m))

int
main(int argc, char *argv[])
{
	off_t data, hole, off, size;
	struct stat st;
	int fd;

	if (argc != 2)
		errx(1, USAGE, getprogname());

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		err(1, "%s", argv[1]);

	if (fstat(fd, &st) == -1)
		err(1, "fstat");

	size = st.st_size;
	off = 0;

	while (off < size) {
		data = lseek(fd, off, SEEK_DATA);
		if (data == -1) {
			if (errno == ENXIO) {
				print(hole, off, size);
				break;
			}
			err(1, "lseek SEEK_DATA");
		}
		if (data > off)
			print(hole, off, data);
		hole = lseek(fd, data, SEEK_HOLE);
		if (hole == -1)
			err(1, "lseek SEEK_HOLE");
		print(data, data, hole);
		off = hole;
	}

	(void)close(fd);
	return (0);
}
