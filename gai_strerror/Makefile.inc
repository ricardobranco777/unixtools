
gerrnos.h:
	@echo '#include <netdb.h>' | $(CC) -E -dD - -D_GNU_SOURCE | \
	awk '$$1 == "#define" && $$2 ~ /^EAI_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vE 'EAI_MAX' | sort -u > $@
