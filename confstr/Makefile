.include "${.CURDIR}/Makefile.inc"

PROG=	confstr
HDRS=	confstrs.h
SRCS=	confstr.c
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
