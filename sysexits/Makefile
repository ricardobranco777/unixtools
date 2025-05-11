.include "${.CURDIR}/Makefile.inc"

PROG=	sysexits
WARNS=	3
WARNINGS=	yes
CFLAGS+= -O2
HDRS=	exits.h
SRCS=	sysexits.c common.c common.h
SRCS+=	${HDRS}
CLEANFILES+=	${HDRS}
MK_DEBUG_FILES=	no

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
