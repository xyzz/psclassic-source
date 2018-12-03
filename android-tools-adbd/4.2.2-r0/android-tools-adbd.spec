Summary: android-tools-adbd version 4.2.2-r0
Name: android-tools-adbd
Version: 4.2.2
Release: r0
License: Apache-2.0 & GPL-2.0 & BSD-2-Clause & BSD-3-Clause
Group: console/utils
Packager: meta-mediatek-aud
BuildRequires: openssl
BuildRequires: systemd-systemctl-native
BuildRequires: virtual/arm-poky-linux-gnueabi-compilerlibs
BuildRequires: virtual/arm-poky-linux-gnueabi-gcc
BuildRequires: virtual/libc
BuildRequires: zlib
Requires: /bin/sh
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.4)
Requires: libc6 >= 2.24
Requires: libcrypto.so.1.0.0
Requires: libcrypto.so.1.0.0(OPENSSL_1.0.2d)
Requires: libcrypto1.0.0 >= 1.0.2j
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: libz.so.1
Requires: libz1 >= 1.2.8
Requires: rtld(GNU_HASH)
Requires(post): /bin/sh
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc6 >= 2.24
Requires(post): libcrypto.so.1.0.0
Requires(post): libcrypto.so.1.0.0(OPENSSL_1.0.2d)
Requires(post): libcrypto1.0.0 >= 1.0.2j
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): libz.so.1
Requires(post): libz1 >= 1.2.8
Requires(post): rtld(GNU_HASH)
Requires(preun): /bin/sh
Requires(preun): libc.so.6
Requires(preun): libc.so.6(GLIBC_2.4)
Requires(preun): libc6 >= 2.24
Requires(preun): libcrypto.so.1.0.0
Requires(preun): libcrypto.so.1.0.0(OPENSSL_1.0.2d)
Requires(preun): libcrypto1.0.0 >= 1.0.2j
Requires(preun): libpthread.so.0
Requires(preun): libpthread.so.0(GLIBC_2.4)
Requires(preun): libz.so.1
Requires(preun): libz1 >= 1.2.8
Requires(preun): rtld(GNU_HASH)
Provides: elf(buildid) = e2ac1e235e158e2df6c987d42ca6598b0687e436

%description
Different utilities from Android - based on the corresponding ubuntu
package

%package -n android-tools-adbd-dbg
Summary: android-tools-adbd version 4.2.2-r0 - Debugging files
Group: devel
Suggests: libc6-dbg
Suggests: libcrypto-dbg
Suggests: libz-dbg

%description -n android-tools-adbd-dbg
Different utilities from Android - based on the corresponding ubuntu
package  This package contains ELF symbols and related sources for
debugging purposes.

%package -n android-tools-adbd-staticdev
Summary: android-tools-adbd version 4.2.2-r0 - Development files (Static Libraries)
Group: devel
Requires: android-tools-adbd-dev = 4.2.2-r0

%description -n android-tools-adbd-staticdev
Different utilities from Android - based on the corresponding ubuntu
package  This package contains static libraries for software development.

%package -n android-tools-adbd-dev
Summary: android-tools-adbd version 4.2.2-r0 - Development files
Group: devel
Requires: android-tools-adbd = 4.2.2-r0
Suggests: libc6-dev
Suggests: libcrypto-dev
Suggests: libz-dev
Suggests: openssl-dev

%description -n android-tools-adbd-dev
Different utilities from Android - based on the corresponding ubuntu
package  This package contains symbolic links, header files, and related
items necessary for software development.

%package -n android-tools-adbd-doc
Summary: android-tools-adbd version 4.2.2-r0 - Documentation files
Group: doc

%description -n android-tools-adbd-doc
Different utilities from Android - based on the corresponding ubuntu
package  This package contains documentation.

%package -n android-tools-adbd-locale
Summary: android-tools-adbd version 4.2.2-r0
Group: console/utils

%description -n android-tools-adbd-locale
Different utilities from Android - based on the corresponding ubuntu
package

%post
# android-tools-adbd - postinst
#!/bin/sh
OPTS=""

if [ -n "$D" ]; then
    OPTS="--root=$D"
fi

if type systemctl >/dev/null 2>/dev/null; then
	systemctl $OPTS enable android-tools-adbd.service

	if [ -z "$D" -a "enable" = "enable" ]; then
		systemctl --no-block restart android-tools-adbd.service
	fi
fi


%preun
# android-tools-adbd - prerm
#!/bin/sh
if [ "$1" = "0" ] ; then
OPTS=""

if [ -n "$D" ]; then
    OPTS="--root=$D"
fi

if type systemctl >/dev/null 2>/dev/null; then
	if [ -z "$D" ]; then
		systemctl stop android-tools-adbd.service
	fi

	systemctl $OPTS disable android-tools-adbd.service
fi
fi

%files
%defattr(-,-,-,-)
%dir "/lib"
%dir "/usr"
%dir "/lib/systemd"
%dir "/lib/systemd/system"
"/lib/systemd/system/android-tools-adbd.service"
%dir "/usr/bin"
"/usr/bin/android-gadget-setup"
"/usr/bin/adbd"

%files -n android-tools-adbd-dbg
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/src"
%dir "/usr/bin"
%dir "/usr/src/debug"
%dir "/usr/src/debug/android-tools-adbd"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libzipfile"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libzipfile/centraldir.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libzipfile/private.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libzipfile/zipfile.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/list.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/abort_socket.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_network_client.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_local_server.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/load_file.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_loopback_server.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/android_reboot.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_loopback_client.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_local_client.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_local.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/libcutils/socket_inaddr_any_server.c"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/zipfile"
%dir "/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/mincrypt"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils/sockets.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils/abort_socket.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils/android_reboot.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils/list.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/cutils/logger.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/zipfile/zipfile.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/include/mincrypt/rsa.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/adb_auth_client.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/jdwp_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/adb.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/services.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/adb.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/backup_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/framebuffer_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/transport.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/adb_auth.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/utils.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/usb_linux_client.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/android_filesystem_config.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/transport.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/sysdeps.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/file_sync_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/file_sync_service.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/remount_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/fdevent.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/transport_usb.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/arpa_nameser.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/base64.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/log_service.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/transport_local.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/mutex_list.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/sockets.c"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/qemu_pipe.h"
"/usr/src/debug/android-tools-adbd/4.2.2-r0/android-tools/core/adbd/fdevent.c"
%dir "/usr/bin/.debug"
"/usr/bin/.debug/adbd"

%files -n android-tools-adbd-dev
%defattr(-,-,-,-)

