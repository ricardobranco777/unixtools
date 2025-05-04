.include "${.CURDIR}/Makefile.inc"

PROG=	sysexits
WARNS=	3
CFLAGS+= -O2
HDRS=	exits.h
SRCS=	sysexits.c common.c common.h
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MK_DEBUG_FILES=	no

.include "${.CURDIR}/../Makefile.bsdinc"
.include <bsd.prog.mk>
