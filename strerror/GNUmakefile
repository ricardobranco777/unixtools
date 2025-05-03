BIN	= strerror strsignal gai_strerror
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= strerror.c common.c
HDRS	= errnos.h signos.h gerrnos.h common.h

OSTYPE	!= uname
ifeq ($(OSTYPE),SunOS)
LDFLAGS	+= -lsocket -lnsl
endif

.PHONY: all
all:	$(BIN)

strerror: $(SRCS) $(HDRS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $(SRCS)

strsignal: $(SRCS) $(HDRS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $(SRCS)

gai_strerror: $(SRCS) $(HDRS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $(SRCS)

.PHONY: clean
clean:
	$(RM) $(BIN) errnos.h signos.h gerrnos.h

.PHONY: test
test:
	./test.sh

include Makefile.inc
