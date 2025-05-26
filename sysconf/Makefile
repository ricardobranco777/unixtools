.include "${.CURDIR}/Makefile.inc"

PROG=	sysconf
HDRS=	sysconfs.h
SRCS=	sysconf.c
SRCS+=	${HDRS}
CLEANFILES+= ${HDRS}
MAN=

MK_DEBUG_FILES=	no
WARNINGS=	yes
WARNS=		3

.include "${.CURDIR}/../Makefile.inc"
.include <bsd.prog.mk>
