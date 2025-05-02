BIN	= strerror strsignal
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
HDRS	= errnos.h signos.h

.PHONY: all
all:	$(BIN)

strerror: strerror.c $(HDRS)
	$(CC) -o strerror $(LDFLAGS) $(CFLAGS) $<

strsignal: strerror.c $(HDRS)
	$(CC) -o strsignal $(LDFLAGS) $(CFLAGS) $<

errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vw ELAST | sort -u > $@

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'SIG(RTMIN|RTMAX|STKSZ)' | sort -u > $@

.PHONY: clean
clean:
	$(RM) $(BIN) $(HDRS)

.PHONY: test
test:
	./test.sh
