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

exits.h:
	@echo '#include <sysexits.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^EX_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' > $@

.PHONY: clean
clean:
	$(RM) $(BIN) exits.h
