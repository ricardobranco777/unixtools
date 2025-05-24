SUBDIRS := ipcmod shmcat strerror sysexits

.PHONY: all install clean $(SUBDIRS)

all:	$(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

install clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
