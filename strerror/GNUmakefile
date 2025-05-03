BIN	= strerror strsignal
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= strerror.c common.c
HDRS	= errnos.h signos.h common.h

.PHONY: all
all:	$(BIN)

strerror: $(SRCS) $(HDRS)
	$(CC) -o strerror $(LDFLAGS) $(CFLAGS) $(SRCS)

strsignal: $(SRCS) $(HDRS)
	$(CC) -o strsignal $(LDFLAGS) $(CFLAGS) $(SRCS)

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
	$(RM) $(BIN) errnos.h signos.h

.PHONY: test
test:
	./test.sh
