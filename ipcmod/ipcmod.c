/* SPDX-License-Identifier: BSD-2-Clause */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <sched.h>
#endif

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

#ifdef CLONE_NEWIPC
#define USAGE	"%s [-i PID] -m|-q|-s MODE SHMID|MSQID|SEMID..."
#else
#define USAGE	"Usage: %s -m|-q|-s MODE SHMID|MSQID|SEMID..."
#endif

static void
msgmod(char *argv[], unsigned short mode)
{
	struct msqid_ds info;
	int id;

	while (*++argv != NULL) {
		if ((id = xatoi(*argv)) < 0)
			errx(1, "invalid number: %s", *argv);
		if (msgctl(id, IPC_STAT, &info) == -1)
			err(1, "IPC_STAT: %d", id);

		info.msg_perm.mode = mode;
		if (msgctl(id, IPC_SET, &info) == -1)
			err(1, "IPC_SET: %d", id);
	}
}

static void
semmod(char *argv[], unsigned short mode)
{
	struct semid_ds info;
	int id;

	while (*++argv != NULL) {
		if ((id = xatoi(*argv)) < 0)
			errx(1, "invalid number: %s", *argv);
		if (semctl(id, 0, IPC_STAT, &info) == -1)
			err(1, "IPC_STAT: %d", id);

		info.sem_perm.mode = mode;
		if (semctl(id, 0, IPC_SET, &info) == -1)
			err(1, "IPC_SET: %d", id);
	}
}

static void
shmmod(char *argv[], unsigned short mode)
{
	struct shmid_ds info;
	int id;

	while (*++argv != NULL) {
		if ((id = xatoi(*argv)) < 0)
			errx(1, "invalid number: %s", *argv);
		if (shmctl(id, IPC_STAT, &info) == -1)
			err(1, "IPC_STAT: %d", id);

		info.shm_perm.mode = mode;
		if (shmctl(id, IPC_SET, &info) == -1)
			err(1, "IPC_SET: %d", id);

#ifdef SHM_LOCKED
		if ((mode & SHM_DEST) != 0 && shmctl(id, IPC_RMID, NULL) == -1)
			err(1, "IPC_RMID: %d", id);

		int cmd;
		if (mode & SHM_LOCKED)
			cmd = info.shm_perm.mode & SHM_LOCKED ? 0 : SHM_LOCK;
		else
			cmd = info.shm_perm.mode & SHM_LOCKED ? SHM_UNLOCK : 0;

		if (cmd) {
			void *addr;
			/*
			 * shmat() may fail if we are the last process attached
			 * and SHM_RMID was set
			 * */
			if ((addr = shmat(id, NULL, SHM_RDONLY)) == (void *) -1)
				continue;
			if (shmctl(id, cmd, NULL) == -1)
				err(1, "shmctl: %d", id);
			if (shmdt(addr) == -1)
				err(1, "shmdt: %d", id);
		}
#endif
	}
}

typedef void (*ipcmod_t)(char *argv[], unsigned short);

int
main(int argc, char *argv[])
{
	ipcmod_t ipcmod = NULL;
	unsigned short mode;
	int mask = 0777;
	int opt;
#ifdef CLONE_NEWIPC
	char path[PATH_MAX];
	int fd = -1;
	pid_t pid;
#endif

#ifdef CLONE_NEWIPC
	while ((opt = getopt(argc, argv, "i:mqs")) != -1) {
#else
	while ((opt = getopt(argc, argv, "mqs")) != -1) {
#endif
		switch (opt) {
#ifdef CLONE_NEWIPC
		case 'i':
			if (fd != -1)
				errx(1, USAGE, getprogname());
			if ((pid = xatoi(optarg)) < 0)
				errx(1, "invalid number: %s", optarg);
			(void)snprintf(path, PATH_MAX, "/proc/%d/ns/ipc", pid);
			if ((fd = open(path, O_RDONLY)) == -1)
				err(1, "%s", path);
			break;
#endif
		case 'm':
			if (ipcmod != NULL)
				errx(1, USAGE, getprogname());
			ipcmod = &shmmod;
			mask = 03777;
			break;
		case 's':
			if (ipcmod != NULL)
				errx(1, USAGE, getprogname());
			ipcmod = &semmod;
			break;
		case 'q':
			if (ipcmod != NULL)
				errx(1, USAGE, getprogname());
			ipcmod = &msgmod;
			break;
		default:
			errx(1, USAGE, getprogname());
		}
	}

	if (ipcmod == NULL)
		errx(1, USAGE, getprogname());

	argc -= optind;
	argv += optind;

	if (argc < 2)
		errx(1, USAGE, getprogname());

	char *endptr = NULL;
	mode = (unsigned short) strtoul(*argv, &endptr, 8);
	if (*endptr != '\0' || mode > mask)
		errx(1, "Invalid mode: %s", *argv);

#ifdef CLONE_NEWIPC
	if (fd != -1) {
		if (setns(fd, CLONE_NEWIPC) == -1)
			err(1, "%s", "setns()");
		(void)close(fd);
	}
#endif

	ipcmod(argv, mode & mask);

	return (0);
}
