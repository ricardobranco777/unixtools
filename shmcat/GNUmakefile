BIN	= shmcat
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= $(BIN).c ../common.c
HDRS	= ../common.h

.PHONY: all
all:	$(BIN)

$(BIN):	$(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include ../GNUmakefile.inc
