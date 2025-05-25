confstrs.h:
	@echo '#include <unistd.h>' | $(CC) -E -dD - -D_GNU_SOURCE | \
	awk '$$1 == "#define" && $$2 ~ /^_CS_[A-Z0-9_]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	sort -u > $@
