.include "${.CURDIR}/Makefile.inc"

PROG=	confstr
WARNS=	3
WARNINGS= yes
CFLAGS+= -O2
HDRS=	confstrs.h
SRCS=	confstr.c common.h
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=
MK_DEBUG_FILES=	no

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
