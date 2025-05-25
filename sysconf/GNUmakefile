BIN	= sysconf
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= $(BIN).c
HDRS	= sysconfs.h common.h
CLEANFILES= sysconfs.h

.PHONY: all
all:	$(BIN)

sysconf: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
