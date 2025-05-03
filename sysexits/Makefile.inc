
exits.h:
	@echo '#include <sysexits.h>' | $(CC) -E -dD - | \
	awk '$$1 == "#define" && $$2 ~ /^EX_[A-Z0-9]+$$/ { printf "{ %s, \"%s\" },\n", $$2, $$2 }' > $@
