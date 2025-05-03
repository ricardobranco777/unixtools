OPSYS:sh = uname
PROG=	sysexits
WARNS=	3
CFLAGS+= -O2
HDRS=	exits.h common.h
SRCS=	sysexits.c common.c
CLEANFILES+=	exits.h

MK_DEBUG_FILES=	no

.if ${OPSYS} == "OpenBSD"
CFLAGS+= -Wall -Wextra
.endif

.if ${OPSYS} != "DragonFly"
${PROG}: ${SRCS} ${HDRS}
.endif

exits.h:
	@echo '#include <sysexits.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^EX_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' > $@

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

.include <bsd.prog.mk>
