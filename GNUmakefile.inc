BINDIR	=	/usr/local/bin
MANDIR	=	/usr/local/share/man/man1
CLEANFILES+=	$(BIN)

OSTYPE  != uname
ifeq ($(OSTYPE),SunOS)
INSTALL	=	ginstall
else
INSTALL	=	install
endif

.PHONY: install
install: $(BIN)
	$(INSTALL) -s -m 555 $(BIN) $(BINDIR)
	$(INSTALL) -m 444 $(BIN).1 $(MANDIR)

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
