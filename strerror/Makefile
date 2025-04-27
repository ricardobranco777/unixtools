OPSYS:sh = uname
PROG=	strerror
WARNS=	3
CFLAGS+= -O2
HDRS+=	errnos.h
CLEANFILES+=	errnos.h

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

errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | grep -vw ELAST | sort -u > $@

$(PROG): errnos.h

.include <bsd.prog.mk>
