PREFIX	?=	/usr/local
BINDIR	=	$(DESTDIR)$(PREFIX)/bin
MANDIR	=	$(DESTDIR)$(PREFIX)/share/man/man1
CLEANFILES+=	$(BIN)

OSTYPE  != uname
ifeq ($(OSTYPE),SunOS)
INSTALL	=	/usr/gnu/bin/install
else
INSTALL	=	install
endif

LDFLAGS	+= -s

.PHONY: install
install: $(BIN)
	$(INSTALL) -C -D -m 555 -t $(BINDIR) $(BIN)
	$(INSTALL) -C -D -m 444 -t $(MANDIR) $(BIN).1

.PHONY: clean
clean:
	$(RM) $(CLEANFILES)
