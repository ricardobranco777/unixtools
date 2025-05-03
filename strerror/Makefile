.include "${.CURDIR}/Makefile.inc"

OPSYS:sh = uname
PROG=	strerror
WARNS=	3
CFLAGS+= -O2
HDRS=	errnos.h signos.h gerrnos.h
SRCS=	strerror.c common.c common.h
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MAN=	strerror.1 strsignal.1 gai_strerror.1
MK_DEBUG_FILES=	no

LINKS=		${BINDIR}/strerror ${BINDIR}/strsignal \
		${BINDIR}/strerror ${BINDIR}/gai_strerror

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

.if ${OPSYS} == "NetBSD" || ${OPSYS} == "OpenBSD"
${PROG}:	${SRCS}
.endif

.include <bsd.prog.mk>
