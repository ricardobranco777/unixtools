BIN	= sigwincher
CC	= gcc
CFLAGS	= -Wall -Wextra -O2
LDFLAGS	=

$(BIN):	$(BIN).c
	$(CC) -o $@ $(BIN).c $(LDFLAGS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(BIN)

.PHONY: install
install:
	install -s -m 0755 $(BIN) /usr/local/bin/ 2>/dev/null || install -s -m 0755 $(BIN) $(HOME)/bin/

.PHONY: uninstall
uninstall:
	$(RM) /usr/local/bin/$(BIN) 2>/dev/null || $(RM) $(HOME)/bin/$(BIN)
