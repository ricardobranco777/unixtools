.include "${.CURDIR}/Makefile.inc"

OPSYS:sh = uname
PROG=	sysexits
WARNS=	3
CFLAGS+= -O2
HDRS=	exits.h
SRCS=	sysexits.c common.c common.h
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MK_DEBUG_FILES=	no

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

.if ${OPSYS} == "NetBSD" || ${OPSYS} == "OpenBSD"
${PROG}:       ${SRCS}
.endif

.include <bsd.prog.mk>
