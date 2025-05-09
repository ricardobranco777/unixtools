BIN	= sysexits
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= sysexits.c common.c
HDRS	= exits.h common.h
CLEANFILES=	exits.h

.PHONY: all
all:	$(BIN)

$(BIN): $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
