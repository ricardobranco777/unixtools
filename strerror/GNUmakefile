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

errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vw ELAST | sort -u > $@

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'SIG(RTMIN|RTMAX|STKSZ)' | sort -u > $@

gerrnos.h:
	@echo '#include <netdb.h>' | $(CC) -E -dD - -D_GNU_SOURCE | \
	awk '$$1 == "#define" && $$2 ~ /^EAI_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'EAI_MAX' | sort -u > $@

.PHONY: clean
clean:
	$(RM) $(BIN) errnos.h signos.h gerrnos.h

.PHONY: test
test:
	./test.sh
