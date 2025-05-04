/* SPDX-License-Identifier: BSD-2-Clause */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/shm.h>
#ifdef __linux__
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <sched.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

#include "common.h"

#ifdef CLONE_NEWIPC
#define USAGE	"%s [-i PID] SHMID"
#else
#define USAGE	"%s SHMID"
#endif

int
main(int argc, char *argv[])
{
	struct shmid_ds info;
	void *addr;
	int opt;
	int id;
#ifdef CLONE_NEWIPC
	char path[PATH_MAX];
	int fd = -1;
	pid_t pid;
#endif

#ifdef CLONE_NEWIPC
	while ((opt = getopt(argc, argv, "i:")) != -1) {
#else
	while ((opt = getopt(argc, argv, "")) != -1) {
#endif
		switch (opt) {
#ifdef CLONE_NEWIPC
		case 'i':
			if (fd != -1)
				errx(1, USAGE, getprogname());
			if ((pid = xatoi(optarg)) < 0)
				errx(1, "invalid number: %s", optarg);
			(void)snprintf(path, PATH_MAX, "/proc/%d/ns/ipc", pid);
			if ((fd = open(path, O_RDONLY)) < 0)
				err(1, "%s", path);
			break;
#endif
		default:
			errx(1, USAGE, getprogname());
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1)
		errx(1, USAGE, getprogname());

	if ((id = xatoi(argv[0])) < 0)
		errx(1, "invalid number: %s", argv[0]);

#ifdef CLONE_NEWIPC
	if (fd != -1) {
		if (setns(fd, CLONE_NEWIPC) == -1)
			err(1, "%s", "setns");
		(void)close(fd);
	}
#endif

	if (shmctl(id, IPC_STAT, &info) == -1)
		err(1, "%s", argv[0]);

	if ((addr = shmat(id, NULL, SHM_RDONLY)) == (void *) -1)
		err(1, "%s", "shmat");

	if (fwrite(addr, info.shm_segsz, 1, stdout) != 1)
		errx(1, "truncated write");

	if (shmdt(addr) == -1)
		err(1, "shmdt");

	return (0);
}
