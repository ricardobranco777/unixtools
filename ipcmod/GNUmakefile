BIN	= ipcmod
BINDIR	= /usr/local/bin/

CC	= gcc
CFLAGS	= -Wall -O2

.PHONY: all
all:	$(BIN)

$(BIN):	$(BIN).c
	$(CC) -o $@ $(CFLAGS) $< common.c

.PHONY: install
install: $(BIN)
	@install -s -m 755 $(BIN) $(BINDIR)

.PHONY: uninstall
uninstall:
	@rm -f $(BINDIR)/$(BIN)

.PHONY: clean
clean:
	@rm -f $(BIN) *.o
