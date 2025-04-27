OPSYS:sh = uname
PROG=	strsignal
WARNS=	3
CFLAGS+= -O2
HDRS+=	signos.h
CLEANFILES+=	signos.h

MK_DEBUG_FILES=	no
MAN=

.if ${OPSYS} == "OpenBSD"
CFLAGS+= -Wall -Wextra
.endif

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

$(PROG): signos.h

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ && $$2 !~ /SIG(RTMIN|RTMAX|STKSZ)/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | sort -u > $@

.include <bsd.prog.mk>
