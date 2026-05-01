BIN	= getrlimit
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= getrlimit.c ../common.c
HDRS	= rlimits.h ../common.h
CLEANFILES=	rlimits.h

.PHONY: all
all:	$(BIN)

$(BIN): $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
