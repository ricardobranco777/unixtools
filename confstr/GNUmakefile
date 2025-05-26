BIN	= confstr
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= $(BIN).c
HDRS	= confstrs.h ../common.h
CLEANFILES= confstrs.h

.PHONY: all
all:	$(BIN)

confstr: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
