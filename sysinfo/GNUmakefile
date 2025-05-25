BIN	= sysinfo
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=
SRCS	= $(BIN).c
HDRS	= sysinfos.h common.h
CLEANFILES= sysinfos.h

.PHONY: all
all:	$(BIN)

sysinfo: $(SRCS) $(HDRS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRCS)

sysinfos.h:
	@echo '#include <sys/systeminfo.h>' | $(CC) -E -dD - | \
        awk '$$1 == "#define" && $$2 ~ /^SI_[A-Z0-9_]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
        grep -v SI_SET | sort -u > $@

include ../GNUmakefile.inc
