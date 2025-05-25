BINDIR	=	/usr/local/bin
MANDIR	=	/usr/local/share/man/man1
CLEANFILES+=	$(BIN)

OSTYPE  != uname
ifeq ($(OSTYPE),SunOS)
INSTALL	=	/usr/gnu/bin/install
else
INSTALL	=	install
endif

.PHONY: install
install: $(BIN)
	$(INSTALL) -D -s -m 555 -t $(BINDIR) $(BIN)
	$(INSTALL) -D -m 444 -t $(MANDIR) $(BIN).1

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
