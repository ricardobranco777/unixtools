BIN	= strerror strsignal gai_strerror
CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -I. -I..
LDFLAGS	=
SRCS	= strerror.c ../common.c
HDRS	= errnos.h signos.h gerrnos.h ../common.h
CLEANFILES= errnos.h signos.h gerrnos.h

OSTYPE	!= uname
ifeq ($(OSTYPE),SunOS)
LDFLAGS	+= -lsocket -lnsl
endif

.PHONY: all
all:	$(BIN)

strerror: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

strsignal gai_strerror: strerror
	ln -f $^ $@ 2>/dev/null || cp -f $^ $@

.PHONY: test
test:
	./test.sh

include Makefile.inc ../GNUmakefile.inc
