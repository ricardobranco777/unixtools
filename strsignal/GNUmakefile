BIN	= strsignal
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= strsignal.c ../common.c
HDRS	= signos.h ../common.h
CLEANFILES= signos.h gerrnos.h

.PHONY: all
all:	$(BIN)

strsignal: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include Makefile.inc ../GNUmakefile.inc
