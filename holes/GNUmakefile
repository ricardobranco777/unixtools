BIN	= holes
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= holes.c
HDRS	= ../common.h
CLEANFILES=

.PHONY: all
all:	$(BIN)

holes: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include ../GNUmakefile.inc
