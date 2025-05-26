.include "${.CURDIR}/Makefile.inc"

.PATH:	${.CURDIR}/..

PROG=	sysexits
HDRS=	exits.h
SRCS=	sysexits.c common.c
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
