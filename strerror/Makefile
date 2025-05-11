.include "${.CURDIR}/Makefile.inc"

PROG=	strerror
WARNS=	3
WARNINGS=	yes
CFLAGS+= -O2
HDRS=	errnos.h signos.h gerrnos.h
SRCS=	strerror.c common.c common.h
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MAN=	strerror.1 strsignal.1 gai_strerror.1
MK_DEBUG_FILES=	no

LINKS=		${BINDIR}/strerror ${BINDIR}/strsignal \
		${BINDIR}/strerror ${BINDIR}/gai_strerror

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
