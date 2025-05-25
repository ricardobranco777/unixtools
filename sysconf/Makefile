.include "${.CURDIR}/Makefile.inc"

PROG=	sysconf
WARNS=	3
WARNINGS= yes
CFLAGS+= -O2
HDRS=	sysconfs.h
SRCS=	sysconf.c common.h
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=
MK_DEBUG_FILES=	no

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
