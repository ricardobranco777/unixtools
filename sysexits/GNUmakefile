BIN	= sysexits
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= sysexits.c common.c
HDRS	= exits.h common.h

.PHONY: all
all:	$(BIN)

sysexits: $(SRCS) $(HDRS)
	$(CC) -o sysexits $(LDFLAGS) $(CFLAGS) $(SRCS)

.PHONY: clean
clean:
	$(RM) $(BIN) exits.h

include Makefile.inc
