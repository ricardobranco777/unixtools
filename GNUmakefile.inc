BINDIR	=	/usr/local/bin
CLEANFILES+=	$(BIN)

.PHONY: install
install: $(BIN)
	install -s -m 555 $(BIN) $(BINDIR)

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
