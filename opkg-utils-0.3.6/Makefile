UTILS = opkg-build opkg-unbuild opkg-make-index opkg.py opkg-list-fields \
	arfile.py opkg-buildpackage opkg-diff opkg-extract-file opkg-show-deps \
	opkg-compare-indexes update-alternatives

MANPAGES = opkg-build.1

DESTDIR =
PREFIX ?= /usr/local
bindir ?= $(PREFIX)/bin
mandir ?= $(PREFIX)/man

.SUFFIXES: .1

%.1: %
	pod2man -r "" -c "opkg-utils Documentation" $< $@

all: $(UTILS) $(MANPAGES)

install: all
	install -d $(DESTDIR)$(bindir)
	install -m 755 $(UTILS) $(DESTDIR)$(bindir)
	install -d $(DESTDIR)$(mandir)
	for m in $(MANPAGES); \
	do \
		install -d $(DESTDIR)$(mandir)/man$${m##*.}; \
		install -m 644 $(MANPAGES) $(DESTDIR)$(mandir)/man$${m##*.}; \
	done

.PHONY: install all
