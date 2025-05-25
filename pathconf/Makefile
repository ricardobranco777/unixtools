.include "${.CURDIR}/Makefile.inc"

PROG=	pathconf
WARNS=	3
WARNINGS= yes
CFLAGS+= -O2
HDRS=	pathconfs.h
SRCS=	pathconf.c common.h
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=
MK_DEBUG_FILES=	no

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
