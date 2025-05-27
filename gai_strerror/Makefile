.include "${.CURDIR}/Makefile.inc"

.PATH:	${.CURDIR}/..

PROG=	gai_strerror
HDRS=	gerrnos.h
SRCS=	gai_strerror.c common.c
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
