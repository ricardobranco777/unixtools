#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <err.h>
#include <sys/ioctl.h>
#include <termios.h>

#if !defined(TIOCGWINSZ) && defined(TIOCGSIZE)
#define TIOCGWINSZ	TIOCGSIZE
#define winsize		ttysize
#define ws_row		ts_rows
#define ws_col		ts_cols
#endif

volatile sig_atomic_t winch_received = 0;

static int fd = -1;

static void
handle_sigwinch(int sig __attribute__((unused))) {
	winch_received = 1;
}

static void
print_tty_size(void) {
	struct winsize ws;

	if (ioctl(fd, TIOCGWINSZ, &ws) == -1)
		err(1, "ioctl");

	printf("rows: %u, cols: %u\n", ws.ws_row, ws.ws_col);
}

int
main(void) {
	struct sigaction sa;
	char *tty;

	fd = STDERR_FILENO;

	if ((tty = ttyname(fd)) == NULL)
		err(1, "ttyname");
	printf("tty: %s\n", tty);

	if (tcgetpgrp(fd) != getpgrp())
		errx(1, "not a foreground process");

	memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigwinch;

	if (sigaction(SIGWINCH, &sa, NULL) == -1)
		err(1, "sigaction");

	print_tty_size();

	while (1) {
		pause();
		if (winch_received) {
			print_tty_size();
			winch_received = 0;
		}
	}

	return 0;
}
