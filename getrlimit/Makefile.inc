
rlimits.h:
	@echo '#include <sys/resource.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^RLIMIT_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' | \
	grep -vw RLIMIT_NLIMITS | sort -u > $@
