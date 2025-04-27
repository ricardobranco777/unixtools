BIN	= strsignal
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=

.PHONY: all
all:	$(BIN)

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ && $$2 !~ /SIG(RTMIN|RTMAX|STKSZ)/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | sort -u > $@

$(BIN): strsignal.c signos.h
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $<

.PHONY: clean
clean:
	$(RM) $(BIN) signos.h
