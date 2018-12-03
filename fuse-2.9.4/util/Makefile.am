## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -D_FILE_OFFSET_BITS=64 
bin_PROGRAMS = fusermount ulockmgr_server
noinst_PROGRAMS = mount.fuse

# CHANGES Made by Anton Feichtmeir 2014: Removed the extra copy of
# mount_util.c from the /util directory in order to eliminate compiler
# errors stemming from conflicting definitions with libfuse.a functons.

fusermount_SOURCES = fusermount.c 
fusermount_CPPFLAGS = -I$(top_srcdir)/lib


mount_fuse_SOURCES = mount.fuse.c

ulockmgr_server_SOURCES = ulockmgr_server.c
ulockmgr_server_CPPFLAGS = -D_FILE_OFFSET_BITS=64 -D_REENTRANT 
ulockmgr_server_LDFLAGS = -pthread

install-exec-hook:
	-chmod u+s $(DESTDIR)$(bindir)/fusermount
	@if test ! -e $(DESTDIR)/dev/fuse; then \
		$(MKDIR_P) $(DESTDIR)/dev; \
		echo "mknod $(DESTDIR)/dev/fuse -m 0666 c 10 229 || true"; \
		mknod $(DESTDIR)/dev/fuse -m 0666 c 10 229 || true; \
	fi

EXTRA_DIST = udev.rules init_script

MOUNT_FUSE_PATH = @MOUNT_FUSE_PATH@
UDEV_RULES_PATH = @UDEV_RULES_PATH@
INIT_D_PATH = @INIT_D_PATH@

install-exec-local:
	$(MKDIR_P) $(DESTDIR)$(MOUNT_FUSE_PATH)
	$(INSTALL_PROGRAM) $(builddir)/mount.fuse $(DESTDIR)$(MOUNT_FUSE_PATH)/mount.fuse
	$(MKDIR_P) $(DESTDIR)$(INIT_D_PATH)
	$(INSTALL_SCRIPT) $(srcdir)/init_script $(DESTDIR)$(INIT_D_PATH)/fuse
	@if test -x /usr/sbin/update-rc.d; then \
		echo "/usr/sbin/update-rc.d fuse start 34 S . start 41 0 6 . || true"; \
		/usr/sbin/update-rc.d fuse start 34 S . start 41 0 6 . || true; \
	fi

install-data-local:
	$(MKDIR_P) $(DESTDIR)$(UDEV_RULES_PATH)
	$(INSTALL_DATA) $(srcdir)/udev.rules $(DESTDIR)$(UDEV_RULES_PATH)/99-fuse.rules

uninstall-local:
	rm -f $(DESTDIR)$(MOUNT_FUSE_PATH)/mount.fuse
	rm -f $(DESTDIR)$(UDEV_RULES_PATH)/99-fuse.rules
	rm -f $(DESTDIR)$(INIT_D_PATH)/fuse
	@if test -x /usr/sbin/update-rc.d; then \
		echo "/usr/sbin/update-rc.d fuse remove || true"; \
		/usr/sbin/update-rc.d fuse remove || true; \
	fi
