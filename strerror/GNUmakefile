BIN	= strerror
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= strerror.c ../common.c
HDRS	= errnos.h ../common.h
CLEANFILES= errnos.h

.PHONY: all
all:	$(BIN)

strerror: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
