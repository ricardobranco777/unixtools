OPSYS:sh = uname

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

.if ${OPSYS} == "NetBSD" || ${OPSYS} == "OpenBSD"
${PROG}:	${SRCS}
.endif
