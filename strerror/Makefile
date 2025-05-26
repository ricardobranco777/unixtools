.include "${.CURDIR}/Makefile.inc"

.PATH:	${.CURDIR}/..

PROG=	strerror
HDRS=	errnos.h signos.h gerrnos.h
SRCS=	strerror.c common.c
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MAN=	strerror.1 strsignal.1 gai_strerror.1

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

LINKS=		${BINDIR}/strerror ${BINDIR}/strsignal \
		${BINDIR}/strerror ${BINDIR}/gai_strerror

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
