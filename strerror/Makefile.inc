
errnos.h:
	@echo '#include <errno.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^E[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vw ELAST | sort -u > $@

signos.h:
	@echo '#include <signal.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^SIG[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vwE 'SIG(RTMIN|RTMAX|STKSZ)' | sort -u > $@

gerrnos.h:
	@echo '#include <netdb.h>' | $(CC) -E -dD - -D_GNU_SOURCE | \
	awk '$$1 == "#define" && $$2 ~ /^EAI_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'EAI_MAX' | sort -u > $@
