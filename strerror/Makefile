OPSYS:sh = uname
.if ${OPSYS} == "FreeBSD" || ${OPSYS} == "MidnightBSD" || ${OPSYS} == "NetBSD"
PROGS=	strerror strsignal gai_strerror
.else
PROG=	strerror strsignal gai_strerror
.endif
WARNS=	3
CFLAGS+= -O2
HDRS=	errnos.h signos.h gerrnos.h common.h
.if ${OPSYS} == "NetBSD"
SRCS.strerror=		strerror.c common.c
SRCS.strsignal=		strerror.c common.c
SRCS.gai_strerror=	strerror.c common.c
.else
SRCS=	strerror.c common.c
.endif
CLEANFILES+=	errnos.h signos.h gerrnos.h

MK_DEBUG_FILES=	no

.if ${OPSYS} == "OpenBSD"
CFLAGS+= -Wall -Wextra
.endif

.if ${OPSYS} == "FreeBSD" || ${OPSYS} == "MidnightBSD" || ${OPSYS} == "NetBSD"
${PROGS}: ${HDRS}
.else
${PROG}: ${HDRS}
.endif

errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vw ELAST | sort -u > $@

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vwE 'SIG(RTMIN|RTMAX|STKSZ)' | sort -u > $@

gerrnos.h:
	@echo '#include <netdb.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^EAI_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'EAI_MAX' | sort -u > $@

.if ${OPSYS} == "NetBSD"
BINDIR= /usr/pkg/bin
.else
BINDIR= /usr/local/bin
.endif

.if ${OPSYS} == "FreeBSD" || ${OPSYS} == "MidnightBSD"
.include <bsd.progs.mk>
.else
.include <bsd.prog.mk>
.endif
