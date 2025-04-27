OPSYS:sh = uname
PROG=	sigwincher
WARNS=	3
CFLAGS+= -O2

MK_DEBUG_FILES=	no
MAN=

.if ${OPSYS} == "OpenBSD"
CFLAGS+= -Wall -Wextra
.endif

.include <bsd.prog.mk>
