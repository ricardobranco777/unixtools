BINDIR=	/usr/local/bin
CFLAGS+= -I..

OPSYS:sh = uname
.if ${OPSYS} == "NetBSD" || ${OPSYS} == "OpenBSD"
${PROG}:	${SRCS}
.endif
