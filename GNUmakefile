SUBDIRS := confstr gai_strerror iface ipcmod pathconf shmcat strerror strsignal sysconf sysexits wol

OSTYPE  != uname
ifeq ($(OSTYPE),SunOS)
SUBDIRS += sysinfo
endif

.PHONY: all install clean $(SUBDIRS)

all:	$(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

install clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done

test-musl:
	podman run --rm -v $$PWD:/unixtools:z -w /unixtools ghcr.io/ricardobranco777/dockerfiles/musl make
