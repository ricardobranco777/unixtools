BIN	= wol
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= $(BIN).c common.c
HDRS	= common.h

OSTYPE	!= uname
ifeq ($(OSTYPE),SunOS)
LDFLAGS	+= -lsocket -lnsl
endif

.PHONY: all
all:	$(BIN)

$(BIN):	$(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

include ../GNUmakefile.inc
