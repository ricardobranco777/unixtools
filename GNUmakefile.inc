BINDIR	=	/usr/local/bin
MANDIR	=	/usr/local/share/man/man1
CLEANFILES+=	$(BIN)

.PHONY: install
install: $(BIN)
	install -s -m 555 $(BIN) $(BINDIR)
	install -m 444 $(BIN).1 $(MANDIR)

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
