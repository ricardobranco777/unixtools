BIN	= strerror
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=

.PHONY: all
all:	$(BIN)

errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | sort -u > $@

$(BIN): $(BIN).c errnos.h
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $<

.PHONY: clean
clean:
	$(RM) $(BIN) errnos.h
