.include "${.CURDIR}/Makefile.inc"

PROG=	pathconf
HDRS=	pathconfs.h
SRCS=	pathconf.c
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
