.include "${.CURDIR}/Makefile.inc"

.PATH:	${.CURDIR}/..

PROG=	strerror
HDRS=	errnos.h
SRCS=	strerror.c common.c
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
