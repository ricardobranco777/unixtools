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

strsignal: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

gai_strerror: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

.PHONY: test
test:
	./test.sh

include Makefile.inc ../GNUmakefile.inc
