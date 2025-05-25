BIN	= pathconf
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= $(BIN).c
HDRS	= pathconfs.h common.h
CLEANFILES= pathconfs.h

.PHONY: all
all:	$(BIN)

pathconf: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
