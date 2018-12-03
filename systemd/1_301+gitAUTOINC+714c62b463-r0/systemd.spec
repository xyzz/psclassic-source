Summary: A System and service manager
Name: systemd
Version: 301+git0+714c62b463
Release: r0
Epoch: 1
License: GPLv2 & LGPLv2.1
Group: base/shell
Packager: meta-mediatek-aud
URL: http://www.freedesktop.org/wiki/Software/systemd
BuildRequires: autoconf-native
BuildRequires: automake-native
BuildRequires: base-files
BuildRequires: bash-completion
BuildRequires: gettext-native
BuildRequires: gnu-config-native
BuildRequires: intltool-native
BuildRequires: libcap
BuildRequires: libcgroup
BuildRequires: libpam
BuildRequires: libtool-cross
BuildRequires: libtool-native
BuildRequires: perl-native
BuildRequires: pkgconfig-native
BuildRequires: shadow
BuildRequires: shadow-native
BuildRequires: shadow-sysroot
BuildRequires: systemd-systemctl-native
BuildRequires: util-linux
BuildRequires: virtual/arm-poky-linux-gnueabi-compilerlibs
BuildRequires: virtual/arm-poky-linux-gnueabi-gcc
BuildRequires: virtual/gettext
BuildRequires: virtual/libc
BuildRequires: virtual/update-alternatives
Requires: /bin/sh
Requires: base-files
Requires: base-passwd
Requires: dbus-1
Requires: kmod
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libblkid.so.1
Requires: libblkid.so.1(BLKID_2.15)
Requires: libblkid.so.1(BLKID_2.17)
Requires: libblkid.so.1(BLKID_2.18)
Requires: libblkid1 >= 2.28.1
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.10)
Requires: libc.so.6(GLIBC_2.11)
Requires: libc.so.6(GLIBC_2.14)
Requires: libc.so.6(GLIBC_2.16)
Requires: libc.so.6(GLIBC_2.17)
Requires: libc.so.6(GLIBC_2.4)
Requires: libc.so.6(GLIBC_2.5)
Requires: libc.so.6(GLIBC_2.6)
Requires: libc.so.6(GLIBC_2.7)
Requires: libc.so.6(GLIBC_2.8)
Requires: libc.so.6(GLIBC_2.9)
Requires: libc6 >= 2.24
Requires: libcap.so.2
Requires: libcap2 >= 2.25
Requires: libcrypt.so.1
Requires: libcrypt.so.1(GLIBC_2.4)
Requires: libdl.so.2
Requires: libgcc1 >= 6.2.0
Requires: libgcc_s.so.1
Requires: libgcc_s.so.1(GCC_3.5)
Requires: libm.so.6
Requires: libm.so.6(GLIBC_2.15)
Requires: libmount.so.1
Requires: libmount.so.1(MOUNT_2.19)
Requires: libmount.so.1(MOUNT_2.20)
Requires: libmount.so.1(MOUNT_2.26)
Requires: libmount1 >= 2.28.1
Requires: libpam >= 1.3.0
Requires: libpam.so.0
Requires: libpam.so.0(LIBPAM_1.0)
Requires: libpam.so.0(LIBPAM_EXTENSION_1.0)
Requires: libpam.so.0(LIBPAM_MODUTIL_1.0)
Requires: libpam_misc.so.0
Requires: libpam_misc.so.0(LIBPAM_MISC_1.0)
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: libresolv.so.2
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Requires: shadow
Requires: udev = 1:301+git0+714c62b463-r0
Requires: update-alternatives-opkg
Requires: update-rc.d
Requires: util-linux-mount
Requires: volatile-binds
Requires(pre): /bin/sh
Requires(pre): base-files
Requires(pre): base-passwd
Requires(pre): dbus-1
Requires(pre): kmod
Requires(pre): ld-linux-armhf.so.3
Requires(pre): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(pre): libblkid.so.1
Requires(pre): libblkid.so.1(BLKID_2.15)
Requires(pre): libblkid.so.1(BLKID_2.17)
Requires(pre): libblkid.so.1(BLKID_2.18)
Requires(pre): libblkid1 >= 2.28.1
Requires(pre): libc.so.6
Requires(pre): libc.so.6(GLIBC_2.10)
Requires(pre): libc.so.6(GLIBC_2.11)
Requires(pre): libc.so.6(GLIBC_2.14)
Requires(pre): libc.so.6(GLIBC_2.16)
Requires(pre): libc.so.6(GLIBC_2.17)
Requires(pre): libc.so.6(GLIBC_2.4)
Requires(pre): libc.so.6(GLIBC_2.5)
Requires(pre): libc.so.6(GLIBC_2.6)
Requires(pre): libc.so.6(GLIBC_2.7)
Requires(pre): libc.so.6(GLIBC_2.8)
Requires(pre): libc.so.6(GLIBC_2.9)
Requires(pre): libc6 >= 2.24
Requires(pre): libcap.so.2
Requires(pre): libcap2 >= 2.25
Requires(pre): libcrypt.so.1
Requires(pre): libcrypt.so.1(GLIBC_2.4)
Requires(pre): libdl.so.2
Requires(pre): libgcc1 >= 6.2.0
Requires(pre): libgcc_s.so.1
Requires(pre): libgcc_s.so.1(GCC_3.5)
Requires(pre): libm.so.6
Requires(pre): libm.so.6(GLIBC_2.15)
Requires(pre): libmount.so.1
Requires(pre): libmount.so.1(MOUNT_2.19)
Requires(pre): libmount.so.1(MOUNT_2.20)
Requires(pre): libmount.so.1(MOUNT_2.26)
Requires(pre): libmount1 >= 2.28.1
Requires(pre): libpam >= 1.3.0
Requires(pre): libpam.so.0
Requires(pre): libpam.so.0(LIBPAM_1.0)
Requires(pre): libpam.so.0(LIBPAM_EXTENSION_1.0)
Requires(pre): libpam.so.0(LIBPAM_MODUTIL_1.0)
Requires(pre): libpam_misc.so.0
Requires(pre): libpam_misc.so.0(LIBPAM_MISC_1.0)
Requires(pre): libpthread.so.0
Requires(pre): libpthread.so.0(GLIBC_2.4)
Requires(pre): libresolv.so.2
Requires(pre): librt.so.1
Requires(pre): librt.so.1(GLIBC_2.4)
Requires(pre): rtld(GNU_HASH)
Requires(pre): shadow
Requires(pre): udev = 1:301+git0+714c62b463-r0
Requires(pre): update-alternatives-opkg
Requires(pre): update-rc.d
Requires(pre): util-linux-mount
Requires(pre): volatile-binds
Requires(post): /bin/sh
Requires(post): base-files
Requires(post): base-passwd
Requires(post): dbus-1
Requires(post): kmod
Requires(post): ld-linux-armhf.so.3
Requires(post): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(post): libblkid.so.1
Requires(post): libblkid.so.1(BLKID_2.15)
Requires(post): libblkid.so.1(BLKID_2.17)
Requires(post): libblkid.so.1(BLKID_2.18)
Requires(post): libblkid1 >= 2.28.1
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.10)
Requires(post): libc.so.6(GLIBC_2.11)
Requires(post): libc.so.6(GLIBC_2.14)
Requires(post): libc.so.6(GLIBC_2.16)
Requires(post): libc.so.6(GLIBC_2.17)
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc.so.6(GLIBC_2.5)
Requires(post): libc.so.6(GLIBC_2.6)
Requires(post): libc.so.6(GLIBC_2.7)
Requires(post): libc.so.6(GLIBC_2.8)
Requires(post): libc.so.6(GLIBC_2.9)
Requires(post): libc6 >= 2.24
Requires(post): libcap.so.2
Requires(post): libcap2 >= 2.25
Requires(post): libcrypt.so.1
Requires(post): libcrypt.so.1(GLIBC_2.4)
Requires(post): libdl.so.2
Requires(post): libgcc1 >= 6.2.0
Requires(post): libgcc_s.so.1
Requires(post): libgcc_s.so.1(GCC_3.5)
Requires(post): libm.so.6
Requires(post): libm.so.6(GLIBC_2.15)
Requires(post): libmount.so.1
Requires(post): libmount.so.1(MOUNT_2.19)
Requires(post): libmount.so.1(MOUNT_2.20)
Requires(post): libmount.so.1(MOUNT_2.26)
Requires(post): libmount1 >= 2.28.1
Requires(post): libpam >= 1.3.0
Requires(post): libpam.so.0
Requires(post): libpam.so.0(LIBPAM_1.0)
Requires(post): libpam.so.0(LIBPAM_EXTENSION_1.0)
Requires(post): libpam.so.0(LIBPAM_MODUTIL_1.0)
Requires(post): libpam_misc.so.0
Requires(post): libpam_misc.so.0(LIBPAM_MISC_1.0)
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): libresolv.so.2
Requires(post): librt.so.1
Requires(post): librt.so.1(GLIBC_2.4)
Requires(post): rtld(GNU_HASH)
Requires(post): shadow
Requires(post): udev = 1:301+git0+714c62b463-r0
Requires(post): update-alternatives-opkg
Requires(post): update-rc.d
Requires(post): util-linux-mount
Requires(post): volatile-binds
Requires(preun): /bin/sh
Requires(preun): base-files
Requires(preun): base-passwd
Requires(preun): dbus-1
Requires(preun): kmod
Requires(preun): ld-linux-armhf.so.3
Requires(preun): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(preun): libblkid.so.1
Requires(preun): libblkid.so.1(BLKID_2.15)
Requires(preun): libblkid.so.1(BLKID_2.17)
Requires(preun): libblkid.so.1(BLKID_2.18)
Requires(preun): libblkid1 >= 2.28.1
Requires(preun): libc.so.6
Requires(preun): libc.so.6(GLIBC_2.10)
Requires(preun): libc.so.6(GLIBC_2.11)
Requires(preun): libc.so.6(GLIBC_2.14)
Requires(preun): libc.so.6(GLIBC_2.16)
Requires(preun): libc.so.6(GLIBC_2.17)
Requires(preun): libc.so.6(GLIBC_2.4)
Requires(preun): libc.so.6(GLIBC_2.5)
Requires(preun): libc.so.6(GLIBC_2.6)
Requires(preun): libc.so.6(GLIBC_2.7)
Requires(preun): libc.so.6(GLIBC_2.8)
Requires(preun): libc.so.6(GLIBC_2.9)
Requires(preun): libc6 >= 2.24
Requires(preun): libcap.so.2
Requires(preun): libcap2 >= 2.25
Requires(preun): libcrypt.so.1
Requires(preun): libcrypt.so.1(GLIBC_2.4)
Requires(preun): libdl.so.2
Requires(preun): libgcc1 >= 6.2.0
Requires(preun): libgcc_s.so.1
Requires(preun): libgcc_s.so.1(GCC_3.5)
Requires(preun): libm.so.6
Requires(preun): libm.so.6(GLIBC_2.15)
Requires(preun): libmount.so.1
Requires(preun): libmount.so.1(MOUNT_2.19)
Requires(preun): libmount.so.1(MOUNT_2.20)
Requires(preun): libmount.so.1(MOUNT_2.26)
Requires(preun): libmount1 >= 2.28.1
Requires(preun): libpam >= 1.3.0
Requires(preun): libpam.so.0
Requires(preun): libpam.so.0(LIBPAM_1.0)
Requires(preun): libpam.so.0(LIBPAM_EXTENSION_1.0)
Requires(preun): libpam.so.0(LIBPAM_MODUTIL_1.0)
Requires(preun): libpam_misc.so.0
Requires(preun): libpam_misc.so.0(LIBPAM_MISC_1.0)
Requires(preun): libpthread.so.0
Requires(preun): libpthread.so.0(GLIBC_2.4)
Requires(preun): libresolv.so.2
Requires(preun): librt.so.1
Requires(preun): librt.so.1(GLIBC_2.4)
Requires(preun): rtld(GNU_HASH)
Requires(preun): shadow
Requires(preun): udev = 1:301+git0+714c62b463-r0
Requires(preun): update-alternatives-opkg
Requires(preun): update-rc.d
Requires(preun): util-linux-mount
Requires(preun): volatile-binds
Suggests: kernel-module-autofs4
Suggests: kernel-module-ipv6
Suggests: kernel-module-unix
Suggests: os-release
Suggests: systemd-compat-units
Suggests: systemd-serialgetty
Suggests: util-linux-agetty
Suggests: util-linux-fsck
Provides: /sbin/halt
Provides: /sbin/init
Provides: /sbin/poweroff
Provides: /sbin/reboot
Provides: /sbin/runlevel
Provides: /sbin/shutdown
Provides: elf(buildid) = 5e8d1a21103c8bad0b86958d44aeef04a1a67a9c
Provides: elf(buildid) = b844916e19b8fb932564cec63efe9915b9634de5
Provides: elf(buildid) = 28a8380f3424400c58c212fe7b9cd2b2cc86fa68
Provides: elf(buildid) = 964d1e34953de084a420a8163872126c45f495a7
Provides: elf(buildid) = 1561c291d24e1c80d6ed5a0dbab6688cf3ede73c
Provides: elf(buildid) = 68daf973548aec90f1889ca7a6bd587a68dbb45c
Provides: elf(buildid) = b544b00c9a41a53a8fe04a3a8579c4d81428ce5e
Provides: elf(buildid) = 04c4d945ef76d26086cc0c062d4f024149dcbc3d
Provides: elf(buildid) = 51c5d09e79ca86ffe3470a8d46fba3ac8204cc7f
Provides: elf(buildid) = 5adba212f16cef4d6b457f0ba4d67b96f006048c
Provides: elf(buildid) = e94318478fd5240d37dd0d4b646458a55a6bf1b6
Provides: elf(buildid) = 6d6f1dc24eaffa58bcae42ca2f7d2fda51b4fa4f
Provides: elf(buildid) = ea1a968b7d68d0458715d54b85c4b118f830aaf1
Provides: elf(buildid) = 82ea0dbc188ff41b5815e17d88173a792718394f
Provides: elf(buildid) = c6f1faeb9ca2728d8491234b007658e88bd93ab2
Provides: elf(buildid) = 147511438f9a9d89e8dd37cf078aaa59514e29d1
Provides: elf(buildid) = 59e8b85f6ee0334b4bc20d5c0fac1b558e05a336
Provides: elf(buildid) = bf8051d1ca7b55030eda9ee8ce1101b7ca7a1834
Provides: elf(buildid) = fe669c74d61e5c31e4fb8a6875876d89ec29f9e5
Provides: elf(buildid) = 69ea8a909c9b7c6b65546a53279962b177478d8f
Provides: elf(buildid) = c91c2ca64531438a6aa50927c841edb2440d04de
Provides: elf(buildid) = 2613521dd7eb0c9d490cfe20e7f2f43789e00992
Provides: elf(buildid) = af714ca832fd4f1c29484b2f63d72d1b8bbb3834
Provides: elf(buildid) = 0b099fd1e98c45a18efded82f4d7bbd37864cacb
Provides: elf(buildid) = 0505e6545cfb61aeebb383df248be85b88fb36a2
Provides: elf(buildid) = 86e8274c8831966f2e4742a421c4f2eb3fbae6df
Provides: elf(buildid) = 43a8c911bb611cba4dada30df6511f860f17aadb
Provides: elf(buildid) = 4e4c9d94865d97d1771ea4ea4e3be657ddc1b96b
Provides: elf(buildid) = 4c86d51725273dfebe3e0d5569146146b16d6edd
Provides: elf(buildid) = 2d85206315dfb14fe84c8ae98601ad31a8faf223
Provides: elf(buildid) = 96e9cf56909d31b4e491561e78bffc962c75c9f4
Provides: elf(buildid) = 1e29f2b5aac20603de7496c8f4277115b7d46207
Provides: elf(buildid) = 046047729fa6abd2aaa30c43dbc18381e671dce4
Provides: elf(buildid) = 81c355c8346d93946792e06d431acde7f66c74b4
Provides: elf(buildid) = 87bb81020eaa76f5e858c2668a4ffaac7c4f83c8
Provides: elf(buildid) = 964c5b1f1dcc679a7e29d971b8000009ddab6352
Provides: elf(buildid) = 323ba17958261f03470d058d58f2802f9dbea228
Provides: elf(buildid) = 939e1a6c713d3535802b3b72578b4d30b50f4152
Provides: elf(buildid) = dc2aac50a48e1cb6557c2f2b78a3fdf5775ebd63
Provides: elf(buildid) = 2f16ac21083d22be112192908d2ccb31c88e215d
Provides: elf(buildid) = 939c36d673067e3b5d014ca255c9397e349a5517
Provides: elf(buildid) = 1b39ba9595d97ed43e8cc7382f77ecf856e4b161
Provides: elf(buildid) = 6eae81c6146f3a19874c62c8f18eed05b2635caa
Provides: elf(buildid) = 803e203c7828167a871a281f4e1b2c4382b2a317
Provides: elf(buildid) = 699bc16d76dd70ae4719f3ae654ecac686dbf91f
Provides: elf(buildid) = d71433656f3fd42d996fe87aa13325a4a8c9d9bd
Provides: elf(buildid) = 6128c9b734d3dbca91954c03ea58b1eefb458409
Provides: elf(buildid) = f5e9b9edbd1d74992ac8c873726682addb181379
Provides: elf(buildid) = 4c37d000c0713979e76f5df1d749cc4e0cbde079
Provides: elf(buildid) = ba14421e69045222a222240b13306085a6db433d
Provides: elf(buildid) = 7eb777003836945c92a14614e71be953af236240
Provides: elf(buildid) = 2ec6bb5ae5aadc39b66eda635e82cfd0ff491f56
Provides: elf(buildid) = 9d900d9d59a0b245f1a270242fb0281bd302a29c
Provides: elf(buildid) = 52c06eb7edd95e8b2c4e177f77fa02c5498fdaee
Provides: elf(buildid) = b40466caf403101db43c8a3179361b2f3b4dfcbd
Provides: elf(buildid) = 9e981993b467c807e9d7da1d0859d657f278e9f3
Provides: elf(buildid) = 11f58f43ce488c271b1a631ed6c8b8bc9c8cf1f7
Provides: pam_systemd.so

%description
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n udev
Summary: A System and service manager
Group: base/shell
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libblkid.so.1
Requires: libblkid.so.1(BLKID_2.15)
Requires: libblkid.so.1(BLKID_2.17)
Requires: libblkid.so.1(BLKID_2.18)
Requires: libblkid1 >= 2.28.1
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.10)
Requires: libc.so.6(GLIBC_2.14)
Requires: libc.so.6(GLIBC_2.17)
Requires: libc.so.6(GLIBC_2.4)
Requires: libc.so.6(GLIBC_2.6)
Requires: libc.so.6(GLIBC_2.7)
Requires: libc.so.6(GLIBC_2.8)
Requires: libc.so.6(GLIBC_2.9)
Requires: libc6 >= 2.24
Requires: libgcc1 >= 6.2.0
Requires: libgcc_s.so.1
Requires: libgcc_s.so.1(GCC_3.5)
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Provides: elf(buildid) = ec3c3a1fce4cc068dc85ed42a747e121a0835a86
Provides: elf(buildid) = 7a96b44f8e106c10554e7014008a0003d62fd53c
Provides: elf(buildid) = 40bbc4ae868a66930f35165c778d9bd136ced36e
Provides: elf(buildid) = 9d5eb1e40dae7e919f900e7c02aeeb7b0d51cad5
Provides: elf(buildid) = e72e87e6db946a3593a7e51a20cec33a795bd2b8
Provides: elf(buildid) = 146ee4a3c4f06e2d757df829c1cca4fe91648422
Provides: elf(buildid) = ef4661368677ec472614ed81e93d58125eea7fd7
Provides: elf(buildid) = ee56800b18415a5f1ce9abffd87dcf3a7a1e4a7e
Provides: hotplug

%description -n udev
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-initramfs
Summary: A System and service manager
Group: base/shell
Requires: systemd

%description -n systemd-initramfs
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-kernel-install
Summary: A System and service manager
Group: base/shell
Requires: /bin/bash
Requires: bash

%description -n systemd-kernel-install
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-rpm-macros
Summary: A System and service manager
Group: base/shell

%description -n systemd-rpm-macros
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-binfmt
Summary: A System and service manager
Group: base/shell
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.17)
Requires: libc.so.6(GLIBC_2.4)
Requires: libc6 >= 2.24
Requires: libgcc1 >= 6.2.0
Requires: libgcc_s.so.1
Requires: libgcc_s.so.1(GCC_3.5)
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Requires(post): ld-linux-armhf.so.3
Requires(post): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.17)
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc6 >= 2.24
Requires(post): libgcc1 >= 6.2.0
Requires(post): libgcc_s.so.1
Requires(post): libgcc_s.so.1(GCC_3.5)
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): librt.so.1
Requires(post): librt.so.1(GLIBC_2.4)
Requires(post): rtld(GNU_HASH)
Requires(preun): ld-linux-armhf.so.3
Requires(preun): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(preun): libc.so.6
Requires(preun): libc.so.6(GLIBC_2.17)
Requires(preun): libc.so.6(GLIBC_2.4)
Requires(preun): libc6 >= 2.24
Requires(preun): libgcc1 >= 6.2.0
Requires(preun): libgcc_s.so.1
Requires(preun): libgcc_s.so.1(GCC_3.5)
Requires(preun): libpthread.so.0
Requires(preun): libpthread.so.0(GLIBC_2.4)
Requires(preun): librt.so.1
Requires(preun): librt.so.1(GLIBC_2.4)
Requires(preun): rtld(GNU_HASH)
Suggests: kernel-module-binfmt-misc
Provides: elf(buildid) = 039159680b73f877ae48761df89eb829deb08743

%description -n systemd-binfmt
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-pam
Summary: A System and service manager
Group: base/shell

%description -n systemd-pam
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-zsh-completion
Summary: A System and service manager
Group: base/shell

%description -n systemd-zsh-completion
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-xorg-xinitrc
Summary: A System and service manager
Group: base/shell
Requires: /bin/sh

%description -n systemd-xorg-xinitrc
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-dbg
Summary: A System and service manager - Debugging files
Group: devel
Suggests: libc6-dbg
Suggests: libcap-dbg
Suggests: libgcc-s-dbg
Suggests: libpam-dbg
Suggests: util-linux-libblkid-dbg
Suggests: util-linux-libmount-dbg

%description -n systemd-dbg
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains ELF symbols and related sources for debugging
purposes.

%package -n systemd-staticdev
Summary: A System and service manager - Development files (Static Libraries)
Group: devel
Requires: systemd-dev = 1:301+git0+714c62b463-r0

%description -n systemd-staticdev
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains static libraries for software development.

%package -n systemd-dev
Summary: A System and service manager - Development files
Group: devel
Requires: libsystemd0
Requires: libudev1
Requires: systemd = 1:301+git0+714c62b463-r0
Suggests: base-files-dev
Suggests: base-passwd-dev
Suggests: bash-completion-dev
Suggests: bash-dev
Suggests: dbus-dev
Suggests: kmod-dev
Suggests: libc6-dev
Suggests: libcap-dev
Suggests: libcgroup-dev
Suggests: libgcc-s-dev
Suggests: libpam-dev
Suggests: libsystemd-dev
Suggests: libudev-dev
Suggests: shadow-dev
Suggests: shadow-sysroot-dev
Suggests: udev-dev
Suggests: update-alternatives-opkg-dev
Suggests: update-rc.d-dev
Suggests: util-linux-dev
Suggests: util-linux-libblkid-dev
Suggests: util-linux-libmount-dev
Suggests: util-linux-mount-dev
Suggests: volatile-binds-dev

%description -n systemd-dev
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains symbolic links, header files, and related items
necessary for software development.

%package -n systemd-doc
Summary: A System and service manager - Documentation files
Group: doc

%description -n systemd-doc
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains documentation.

%package -n systemd-bash-completion
Summary: A System and service manager
Group: base/shell
Requires: bash-completion

%description -n systemd-bash-completion
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.

%package -n systemd-locale-be
Summary: A System and service manager - be translations
Group: base/shell
Suggests: virtual-locale-be
Provides: be-translation
Provides: systemd-locale

%description -n systemd-locale-be
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the be locale.

%package -n systemd-locale-be+latin
Summary: A System and service manager - be@latin translations
Group: base/shell
Suggests: virtual-locale-be+latin
Provides: be+latin-translation
Provides: systemd-locale

%description -n systemd-locale-be+latin
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the be@latin locale.

%package -n systemd-locale-da
Summary: A System and service manager - da translations
Group: base/shell
Suggests: virtual-locale-da
Provides: da-translation
Provides: systemd-locale

%description -n systemd-locale-da
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the da locale.

%package -n systemd-locale-de
Summary: A System and service manager - de translations
Group: base/shell
Suggests: virtual-locale-de
Provides: de-translation
Provides: systemd-locale

%description -n systemd-locale-de
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the de locale.

%package -n systemd-locale-el
Summary: A System and service manager - el translations
Group: base/shell
Suggests: virtual-locale-el
Provides: el-translation
Provides: systemd-locale

%description -n systemd-locale-el
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the el locale.

%package -n systemd-locale-es
Summary: A System and service manager - es translations
Group: base/shell
Suggests: virtual-locale-es
Provides: es-translation
Provides: systemd-locale

%description -n systemd-locale-es
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the es locale.

%package -n systemd-locale-fr
Summary: A System and service manager - fr translations
Group: base/shell
Suggests: virtual-locale-fr
Provides: fr-translation
Provides: systemd-locale

%description -n systemd-locale-fr
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the fr locale.

%package -n systemd-locale-gl
Summary: A System and service manager - gl translations
Group: base/shell
Suggests: virtual-locale-gl
Provides: gl-translation
Provides: systemd-locale

%description -n systemd-locale-gl
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the gl locale.

%package -n systemd-locale-hu
Summary: A System and service manager - hu translations
Group: base/shell
Suggests: virtual-locale-hu
Provides: hu-translation
Provides: systemd-locale

%description -n systemd-locale-hu
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the hu locale.

%package -n systemd-locale-it
Summary: A System and service manager - it translations
Group: base/shell
Suggests: virtual-locale-it
Provides: it-translation
Provides: systemd-locale

%description -n systemd-locale-it
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the it locale.

%package -n systemd-locale-ko
Summary: A System and service manager - ko translations
Group: base/shell
Suggests: virtual-locale-ko
Provides: ko-translation
Provides: systemd-locale

%description -n systemd-locale-ko
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the ko locale.

%package -n systemd-locale-pl
Summary: A System and service manager - pl translations
Group: base/shell
Suggests: virtual-locale-pl
Provides: pl-translation
Provides: systemd-locale

%description -n systemd-locale-pl
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the pl locale.

%package -n systemd-locale-pt-br
Summary: A System and service manager - pt_BR translations
Group: base/shell
Suggests: virtual-locale-pt-br
Provides: pt-br-translation
Provides: systemd-locale

%description -n systemd-locale-pt-br
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the pt_BR locale.

%package -n systemd-locale-ru
Summary: A System and service manager - ru translations
Group: base/shell
Suggests: virtual-locale-ru
Provides: ru-translation
Provides: systemd-locale

%description -n systemd-locale-ru
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the ru locale.

%package -n systemd-locale-sr
Summary: A System and service manager - sr translations
Group: base/shell
Suggests: virtual-locale-sr
Provides: sr-translation
Provides: systemd-locale

%description -n systemd-locale-sr
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the sr locale.

%package -n systemd-locale-sv
Summary: A System and service manager - sv translations
Group: base/shell
Suggests: virtual-locale-sv
Provides: sv-translation
Provides: systemd-locale

%description -n systemd-locale-sv
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the sv locale.

%package -n systemd-locale-tr
Summary: A System and service manager - tr translations
Group: base/shell
Suggests: virtual-locale-tr
Provides: systemd-locale
Provides: tr-translation

%description -n systemd-locale-tr
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the tr locale.

%package -n systemd-locale-uk
Summary: A System and service manager - uk translations
Group: base/shell
Suggests: virtual-locale-uk
Provides: systemd-locale
Provides: uk-translation

%description -n systemd-locale-uk
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the uk locale.

%package -n systemd-locale-zh-cn
Summary: A System and service manager - zh_CN translations
Group: base/shell
Suggests: virtual-locale-zh-cn
Provides: systemd-locale
Provides: zh-cn-translation

%description -n systemd-locale-zh-cn
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the zh_CN locale.

%package -n systemd-locale-zh-tw
Summary: A System and service manager - zh_TW translations
Group: base/shell
Suggests: virtual-locale-zh-tw
Provides: systemd-locale
Provides: zh-tw-translation

%description -n systemd-locale-zh-tw
systemd is a system and service manager for Linux, compatible with SysV and
LSB init scripts. systemd provides aggressive parallelization capabilities,
uses socket and D-Bus activation for starting services, offers on-demand
starting of daemons, keeps track of processes using Linux cgroups, supports
snapshotting and restoring of the system state, maintains mount and
automount points and implements an elaborate transactional dependency-based
service control logic. It can work as a drop-in replacement for sysvinit.
This package contains language translation files for the zh_TW locale.

%package -n libsystemd0
Summary: Systemd systemd library
Group: base/shell
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.14)
Requires: libc.so.6(GLIBC_2.16)
Requires: libc.so.6(GLIBC_2.17)
Requires: libc.so.6(GLIBC_2.4)
Requires: libc.so.6(GLIBC_2.7)
Requires: libc.so.6(GLIBC_2.8)
Requires: libc.so.6(GLIBC_2.9)
Requires: libc6 >= 2.24
Requires: libcap.so.2
Requires: libcap2 >= 2.25
Requires: libgcc1 >= 6.2.0
Requires: libgcc_s.so.1
Requires: libgcc_s.so.1(GCC_3.5)
Requires: libm.so.6
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: libresolv.so.2
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Requires(post): ld-linux-armhf.so.3
Requires(post): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.14)
Requires(post): libc.so.6(GLIBC_2.16)
Requires(post): libc.so.6(GLIBC_2.17)
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc.so.6(GLIBC_2.7)
Requires(post): libc.so.6(GLIBC_2.8)
Requires(post): libc.so.6(GLIBC_2.9)
Requires(post): libc6 >= 2.24
Requires(post): libcap.so.2
Requires(post): libcap2 >= 2.25
Requires(post): libgcc1 >= 6.2.0
Requires(post): libgcc_s.so.1
Requires(post): libgcc_s.so.1(GCC_3.5)
Requires(post): libm.so.6
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): libresolv.so.2
Requires(post): librt.so.1
Requires(post): librt.so.1(GLIBC_2.4)
Requires(post): rtld(GNU_HASH)
Provides: elf(buildid) = 26b9c80c12a4da1fbd9f4aaaf5b6114bbd8d4f9c
Provides: libsystemd = 301+git0+714c62b463
Provides: libsystemd.so.0
Provides: libsystemd.so.0(LIBSYSTEMD_209)
Provides: libsystemd.so.0(LIBSYSTEMD_211)
Provides: libsystemd.so.0(LIBSYSTEMD_213)
Provides: libsystemd.so.0(LIBSYSTEMD_214)
Provides: libsystemd.so.0(LIBSYSTEMD_216)
Provides: libsystemd.so.0(LIBSYSTEMD_217)
Provides: libsystemd.so.0(LIBSYSTEMD_219)
Provides: libsystemd.so.0(LIBSYSTEMD_220)
Provides: libsystemd.so.0(LIBSYSTEMD_221)
Provides: libsystemd.so.0(LIBSYSTEMD_222)
Provides: libsystemd.so.0(LIBSYSTEMD_226)
Provides: libsystemd.so.0(LIBSYSTEMD_227)
Provides: libsystemd.so.0(LIBSYSTEMD_229)

%description -n libsystemd0
Systemd systemd library

%package -n libudev1
Summary: Systemd udev library
Group: base/shell
Requires: ld-linux-armhf.so.3
Requires: ld-linux-armhf.so.3(GLIBC_2.4)
Requires: libc.so.6
Requires: libc.so.6(GLIBC_2.14)
Requires: libc.so.6(GLIBC_2.4)
Requires: libc.so.6(GLIBC_2.8)
Requires: libc.so.6(GLIBC_2.9)
Requires: libc6 >= 2.24
Requires: libcap.so.2
Requires: libcap2 >= 2.25
Requires: libgcc1 >= 6.2.0
Requires: libgcc_s.so.1
Requires: libgcc_s.so.1(GCC_3.5)
Requires: libm.so.6
Requires: libpthread.so.0
Requires: libpthread.so.0(GLIBC_2.4)
Requires: libresolv.so.2
Requires: librt.so.1
Requires: librt.so.1(GLIBC_2.4)
Requires: rtld(GNU_HASH)
Requires(post): ld-linux-armhf.so.3
Requires(post): ld-linux-armhf.so.3(GLIBC_2.4)
Requires(post): libc.so.6
Requires(post): libc.so.6(GLIBC_2.14)
Requires(post): libc.so.6(GLIBC_2.4)
Requires(post): libc.so.6(GLIBC_2.8)
Requires(post): libc.so.6(GLIBC_2.9)
Requires(post): libc6 >= 2.24
Requires(post): libcap.so.2
Requires(post): libcap2 >= 2.25
Requires(post): libgcc1 >= 6.2.0
Requires(post): libgcc_s.so.1
Requires(post): libgcc_s.so.1(GCC_3.5)
Requires(post): libm.so.6
Requires(post): libpthread.so.0
Requires(post): libpthread.so.0(GLIBC_2.4)
Requires(post): libresolv.so.2
Requires(post): librt.so.1
Requires(post): librt.so.1(GLIBC_2.4)
Requires(post): rtld(GNU_HASH)
Provides: elf(buildid) = 540d60ba8d8c4128837c90c1b27ac0718fea3cb0
Provides: libudev = 301+git0+714c62b463
Provides: libudev.so.1
Provides: libudev.so.1(LIBUDEV_183)
Provides: libudev.so.1(LIBUDEV_189)
Provides: libudev.so.1(LIBUDEV_196)
Provides: libudev.so.1(LIBUDEV_199)
Provides: libudev.so.1(LIBUDEV_215)

%description -n libudev1
Systemd udev library

%pre
# systemd - preinst
#!/bin/sh
bbnote () {
	echo "NOTE: $*"
}
bbwarn () {
	echo "WARNING: $*"
}
bbfatal () {
	echo "ERROR: $*"
	exit 1
}
perform_groupadd () {
	local rootdir="$1"
	local opts="$2"
	bbnote "systemd: Performing groupadd with [$opts]"
	local groupname=`echo "$opts" | awk '{ print $NF }'`
	local group_exists="`grep "^$groupname:" $rootdir/etc/group || true`"
	if test "x$group_exists" = "x"; then
		eval flock -x $rootdir/etc -c \"$PSEUDO groupadd \$opts\" || true
		group_exists="`grep "^$groupname:" $rootdir/etc/group || true`"
		if test "x$group_exists" = "x"; then
			bbfatal "systemd: groupadd command did not succeed."
		fi
	else
		bbnote "systemd: group $groupname already exists, not re-creating it"
	fi
}
perform_useradd () {
	local rootdir="$1"
	local opts="$2"
	bbnote "systemd: Performing useradd with [$opts]"
	local username=`echo "$opts" | awk '{ print $NF }'`
	local user_exists="`grep "^$username:" $rootdir/etc/passwd || true`"
	if test "x$user_exists" = "x"; then
		eval flock -x $rootdir/etc -c  \"$PSEUDO useradd \$opts\" || true
		user_exists="`grep "^$username:" $rootdir/etc/passwd || true`"
		if test "x$user_exists" = "x"; then
			bbfatal "systemd: useradd command did not succeed."
		fi
	else
		bbnote "systemd: user $username already exists, not re-creating it"
	fi
}
perform_groupmems () {
	local rootdir="$1"
	local opts="$2"
	bbnote "systemd: Performing groupmems with [$opts]"
	local groupname=`echo "$opts" | awk '{ for (i = 1; i < NF; i++) if ($i == "-g" || $i == "--group") print $(i+1) }'`
	local username=`echo "$opts" | awk '{ for (i = 1; i < NF; i++) if ($i == "-a" || $i == "--add") print $(i+1) }'`
	bbnote "systemd: Running groupmems command with group $groupname and user $username"
	local mem_exists="`grep "^$groupname:[^:]*:[^:]*:\([^,]*,\)*$username\(,[^,]*\)*" $rootdir/etc/group || true`"
	if test "x$mem_exists" = "x"; then
		eval flock -x $rootdir/etc -c \"$PSEUDO groupmems \$opts\" || true
		mem_exists="`grep "^$groupname:[^:]*:[^:]*:\([^,]*,\)*$username\(,[^,]*\)*" $rootdir/etc/group || true`"
		if test "x$mem_exists" = "x"; then
			bbfatal "systemd: groupmems command did not succeed."
		fi
	else
		bbnote "systemd: group $groupname already contains $username, not re-adding it"
	fi
}
OPT=""
SYSROOT=""

if test "x$D" != "x"; then
	# Installing into a sysroot
	SYSROOT="$D"
	OPT="--root $D"

	# Make sure login.defs is there, this is to make debian package backend work
	# correctly while doing rootfs.
	# The problem here is that if /etc/login.defs is treated as a config file for
	# shadow package, then while performing preinsts for packages that depend on
	# shadow, there might only be /etc/login.def.dpkg-new there in root filesystem.
	if [ ! -e $D/etc/login.defs -a -e $D/etc/login.defs.dpkg-new ]; then
	    cp $D/etc/login.defs.dpkg-new $D/etc/login.defs
	fi

	# user/group lookups should match useradd/groupadd --root
	export PSEUDO_PASSWD="$SYSROOT:/home/lai/Documents/shareData/MTK_RELEASE/0831/build/tmp/sysroots/x86_64-linux"
fi

# If we're not doing a special SSTATE/SYSROOT install
# then set the values, otherwise use the environment
if test "x$UA_SYSROOT" = "x"; then
	# Installing onto a target
	# Add groups and users defined only for this package
	GROUPADD_PARAM="-r lock; -r systemd-journal"
	USERADD_PARAM="  --system -d / -M --shell /bin/nologin systemd-timesync;"
	GROUPMEMS_PARAM="${GROUPMEMS_PARAM}"
fi

# Perform group additions first, since user additions may depend
# on these groups existing
if test "x`echo $GROUPADD_PARAM | tr -d '[:space:]'`" != "x"; then
	echo "Running groupadd commands..."
	# Invoke multiple instances of groupadd for parameter lists
	# separated by ';'
	opts=`echo "$GROUPADD_PARAM" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
	remaining=`echo "$GROUPADD_PARAM" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	while test "x$opts" != "x"; do
		perform_groupadd "$SYSROOT" "$OPT $opts"
		if test "x$opts" = "x$remaining"; then
			break
		fi
		opts=`echo "$remaining" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
		remaining=`echo "$remaining" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	done
fi

if test "x`echo $USERADD_PARAM | tr -d '[:space:]'`" != "x"; then
	echo "Running useradd commands..."
	# Invoke multiple instances of useradd for parameter lists
	# separated by ';'
	opts=`echo "$USERADD_PARAM" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
	remaining=`echo "$USERADD_PARAM" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	while test "x$opts" != "x"; do
		perform_useradd "$SYSROOT" "$OPT $opts"
		if test "x$opts" = "x$remaining"; then
			break
		fi
		opts=`echo "$remaining" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
		remaining=`echo "$remaining" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	done
fi

if test "x`echo $GROUPMEMS_PARAM | tr -d '[:space:]'`" != "x"; then
	echo "Running groupmems commands..."
	# Invoke multiple instances of groupmems for parameter lists
	# separated by ';'
	opts=`echo "$GROUPMEMS_PARAM" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
	remaining=`echo "$GROUPMEMS_PARAM" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	while test "x$opts" != "x"; do
		perform_groupmems "$SYSROOT" "$OPT $opts"
		if test "x$opts" = "x$remaining"; then
			break
		fi
		opts=`echo "$remaining" | cut -d ';' -f 1 | sed -e 's#[ \t]*$##'`
		remaining=`echo "$remaining" | cut -d ';' -f 2- | sed -e 's#[ \t]*$##'`
	done
fi


%post
# systemd - postinst
	sed -e '/^hosts:/s/\s*\<myhostname\>//' \
		-e 's/\(^hosts:.*\)\(\<files\>\)\(.*\)\(\<dns\>\)\(.*\)/\1\2 myhostname \3\4\5/' \
		-i $D/etc/nsswitch.conf
# Begin section update-alternatives
update-alternatives --install /sbin/init init /lib/systemd/systemd 300
update-alternatives --install /sbin/halt halt /bin/systemctl 300
update-alternatives --install /sbin/reboot reboot /bin/systemctl 300
update-alternatives --install /sbin/shutdown shutdown /bin/systemctl 300
update-alternatives --install /sbin/poweroff poweroff /bin/systemctl 300
update-alternatives --install /sbin/runlevel runlevel /bin/systemctl 300
# End section update-alternatives


%preun
# systemd - prerm
if [ "$1" = "0" ] ; then
sed -e '/^hosts:/s/\s*\<myhostname\>//' \
		-e '/^hosts:/s/\s*myhostname//' \
		-i $D/etc/nsswitch.conf
# Begin section update-alternatives
update-alternatives --remove  init /lib/systemd/systemd
update-alternatives --remove  halt /bin/systemctl
update-alternatives --remove  reboot /bin/systemctl
update-alternatives --remove  shutdown /bin/systemctl
update-alternatives --remove  poweroff /bin/systemctl
update-alternatives --remove  runlevel /bin/systemctl
# End section update-alternatives
fi

%post -n systemd-binfmt
# systemd-binfmt - postinst
#!/bin/sh
OPTS=""

if [ -n "$D" ]; then
    OPTS="--root=$D"
fi

if type systemctl >/dev/null 2>/dev/null; then
	systemctl $OPTS enable systemd-binfmt.service

	if [ -z "$D" -a "enable" = "enable" ]; then
		systemctl --no-block restart systemd-binfmt.service
	fi
fi


%preun -n systemd-binfmt
# systemd-binfmt - prerm
#!/bin/sh
if [ "$1" = "0" ] ; then
OPTS=""

if [ -n "$D" ]; then
    OPTS="--root=$D"
fi

if type systemctl >/dev/null 2>/dev/null; then
	if [ -z "$D" ]; then
		systemctl stop systemd-binfmt.service
	fi

	systemctl $OPTS disable systemd-binfmt.service
fi
fi

%post -n libsystemd0
# libsystemd0 - postinst
#!/bin/sh
if [ x"$D" = "x" ]; then
	if [ -x /sbin/ldconfig ]; then /sbin/ldconfig ; fi
fi


%post -n libudev1
# libudev1 - postinst
#!/bin/sh
if [ x"$D" = "x" ]; then
	if [ -x /sbin/ldconfig ]; then /sbin/ldconfig ; fi
fi


%files
%defattr(-,-,-,-)
%dir "/etc"
%dir "/lib"
%dir "/var"
%dir "/bin"
%dir "/usr"
%dir "/etc/tmpfiles.d"
%dir "/etc/modules-load.d"
%dir "/etc/sysctl.d"
%dir "/etc/pam.d"
%dir "/etc/dbus-1"
%dir "/etc/systemd"
%dir "/etc/xdg"
"/etc/resolv.conf"
%config "/etc/machine-id"
"/etc/tmpfiles.d/00-create-volatile.conf"
"/etc/pam.d/systemd-user"
%dir "/etc/dbus-1/system.d"
"/etc/dbus-1/system.d/org.freedesktop.systemd1.conf"
"/etc/dbus-1/system.d/org.freedesktop.login1.conf"
"/etc/dbus-1/system.d/org.freedesktop.timedate1.conf"
%dir "/etc/systemd/network"
%dir "/etc/systemd/user"
%dir "/etc/systemd/system"
%config "/etc/systemd/coredump.conf"
%config "/etc/systemd/journald.conf"
%config "/etc/systemd/logind.conf"
"/etc/systemd/timesyncd.conf"
%config "/etc/systemd/system.conf"
%config "/etc/systemd/user.conf"
%dir "/etc/systemd/system/multi-user.target.wants"
%dir "/etc/systemd/system/getty.target.wants"
%dir "/etc/systemd/system/sysinit.target.wants"
"/etc/systemd/system/multi-user.target.wants/remote-fs.target"
"/etc/systemd/system/getty.target.wants/getty@tty1.service"
"/etc/systemd/system/sysinit.target.wants/systemd-timesyncd.service"
%dir "/etc/xdg/systemd"
"/etc/xdg/systemd/user"
%dir "/lib/systemd"
%dir "/lib/security"
%dir "/lib/systemd/network"
%dir "/lib/systemd/system"
%dir "/lib/systemd/system-shutdown"
%dir "/lib/systemd/system-sleep"
%dir "/lib/systemd/system-preset"
%dir "/lib/systemd/system-generators"
"/lib/systemd/systemd-socket-proxyd"
"/lib/systemd/systemd-update-done"
"/lib/systemd/systemd-timedated"
"/lib/systemd/systemd-journald"
"/lib/systemd/systemd-coredump"
"/lib/systemd/systemd-sleep"
"/lib/systemd/systemd-sysv-install"
"/lib/systemd/systemd-user-sessions"
"/lib/systemd/systemd-reply-password"
"/lib/systemd/systemd-timesyncd"
"/lib/systemd/systemd-cgroups-agent"
"/lib/systemd/systemd-vconsole-setup"
"/lib/systemd/systemd-fsck"
"/lib/systemd/systemd-hibernate-resume"
"/lib/systemd/systemd-update-utmp"
"/lib/systemd/systemd"
"/lib/systemd/systemd-remount-fs"
"/lib/systemd/systemd-shutdown"
"/lib/systemd/systemd-initctl"
"/lib/systemd/systemd-sysctl"
"/lib/systemd/systemd-random-seed"
"/lib/systemd/systemd-ac-power"
"/lib/systemd/systemd-logind"
"/lib/systemd/network/80-container-host0.network"
"/lib/systemd/network/99-default.link"
"/lib/systemd/network/80-container-ve.network"
%dir "/lib/systemd/system/runlevel1.target.wants"
%dir "/lib/systemd/system/reboot.target.wants"
%dir "/lib/systemd/system/rescue.target.wants"
%dir "/lib/systemd/system/timers.target.wants"
%dir "/lib/systemd/system/runlevel5.target.wants"
%dir "/lib/systemd/system/poweroff.target.wants"
%dir "/lib/systemd/system/busnames.target.wants"
%dir "/lib/systemd/system/multi-user.target.wants"
%dir "/lib/systemd/system/local-fs.target.wants"
%dir "/lib/systemd/system/runlevel3.target.wants"
%dir "/lib/systemd/system/sockets.target.wants"
%dir "/lib/systemd/system/runlevel4.target.wants"
%dir "/lib/systemd/system/runlevel2.target.wants"
%dir "/lib/systemd/system/sysinit.target.wants"
%dir "/lib/systemd/system/graphical.target.wants"
"/lib/systemd/system/systemd-journald-audit.socket"
"/lib/systemd/system/exit.target"
"/lib/systemd/system/systemd-journald.service"
"/lib/systemd/system/emergency.target"
"/lib/systemd/system/dbus-org.freedesktop.login1.service"
"/lib/systemd/system/dev-mqueue.mount"
"/lib/systemd/system/systemd-suspend.service"
"/lib/systemd/system/systemd-ask-password-wall.path"
"/lib/systemd/system/runlevel4.target"
"/lib/systemd/system/systemd-update-utmp.service"
"/lib/systemd/system/systemd-journald.socket"
"/lib/systemd/system/systemd-tmpfiles-setup.service"
"/lib/systemd/system/syslog.socket"
"/lib/systemd/system/org.freedesktop.login1.busname"
"/lib/systemd/system/systemd-exit.service"
"/lib/systemd/system/systemd-nspawn@.service"
"/lib/systemd/system/runlevel0.target"
"/lib/systemd/system/systemd-update-done.service"
"/lib/systemd/system/org.freedesktop.timedate1.busname"
"/lib/systemd/system/network-online.target"
"/lib/systemd/system/sockets.target"
"/lib/systemd/system/default.target"
"/lib/systemd/system/systemd-kexec.service"
"/lib/systemd/system/hybrid-sleep.target"
"/lib/systemd/system/system.slice"
"/lib/systemd/system/autovt@.service"
"/lib/systemd/system/timers.target"
"/lib/systemd/system/sys-kernel-debug.mount"
"/lib/systemd/system/getty@.service"
"/lib/systemd/system/org.freedesktop.systemd1.busname"
"/lib/systemd/system/systemd-ask-password-console.path"
"/lib/systemd/system/smartcard.target"
"/lib/systemd/system/ctrl-alt-del.target"
"/lib/systemd/system/debug-shell.service"
"/lib/systemd/system/systemd-journal-flush.service"
"/lib/systemd/system/tmp.mount"
"/lib/systemd/system/systemd-update-utmp-runlevel.service"
"/lib/systemd/system/systemd-ask-password-console.service"
"/lib/systemd/system/initrd-switch-root.service"
"/lib/systemd/system/runlevel6.target"
"/lib/systemd/system/reboot.target"
"/lib/systemd/system/systemd-sysctl.service"
"/lib/systemd/system/systemd-initctl.socket"
"/lib/systemd/system/systemd-tmpfiles-setup-dev.service"
"/lib/systemd/system/paths.target"
"/lib/systemd/system/nss-lookup.target"
"/lib/systemd/system/systemd-machine-id-commit.service"
"/lib/systemd/system/suspend.target"
"/lib/systemd/system/local-fs-pre.target"
"/lib/systemd/system/systemd-ask-password-wall.service"
"/lib/systemd/system/systemd-remount-fs.service"
"/lib/systemd/system/sound.target"
"/lib/systemd/system/swap.target"
"/lib/systemd/system/console-shell.service"
"/lib/systemd/system/systemd-fsck@.service"
"/lib/systemd/system/basic.target"
"/lib/systemd/system/user@.service"
"/lib/systemd/system/system-update.target"
"/lib/systemd/system/console-getty.service"
"/lib/systemd/system/machines.target"
"/lib/systemd/system/systemd-timedated.service"
"/lib/systemd/system/remote-fs.target"
"/lib/systemd/system/rpcbind.target"
"/lib/systemd/system/systemd-firstboot.service"
"/lib/systemd/system/sys-fs-fuse-connections.mount"
"/lib/systemd/system/initrd-cleanup.service"
"/lib/systemd/system/umount.target"
"/lib/systemd/system/systemd-random-seed.service"
"/lib/systemd/system/systemd-hibernate.service"
"/lib/systemd/system/systemd-coredump.socket"
"/lib/systemd/system/halt-local.service"
"/lib/systemd/system/runlevel3.target"
"/lib/systemd/system/initrd.target"
"/lib/systemd/system/runlevel5.target"
"/lib/systemd/system/systemd-initctl.service"
"/lib/systemd/system/systemd-tmpfiles-clean.service"
"/lib/systemd/system/network.target"
"/lib/systemd/system/network-pre.target"
"/lib/systemd/system/halt.target"
"/lib/systemd/system/nss-user-lookup.target"
"/lib/systemd/system/time-sync.target"
"/lib/systemd/system/final.target"
"/lib/systemd/system/initrd-parse-etc.service"
"/lib/systemd/system/user.slice"
"/lib/systemd/system/hibernate.target"
"/lib/systemd/system/shutdown.target"
"/lib/systemd/system/systemd-vconsole-setup.service"
"/lib/systemd/system/systemd-coredump@.service"
"/lib/systemd/system/sleep.target"
"/lib/systemd/system/systemd-journal-catalog-update.service"
"/lib/systemd/system/systemd-logind.service"
"/lib/systemd/system/dbus-org.freedesktop.timedate1.service"
"/lib/systemd/system/slices.target"
"/lib/systemd/system/initrd-switch-root.target"
"/lib/systemd/system/runlevel1.target"
"/lib/systemd/system/-.slice"
"/lib/systemd/system/sysinit.target"
"/lib/systemd/system/quotaon.service"
"/lib/systemd/system/poweroff.target"
"/lib/systemd/system/systemd-tmpfiles-clean.timer"
"/lib/systemd/system/graphical.target"
"/lib/systemd/system/systemd-poweroff.service"
"/lib/systemd/system/rescue.service"
"/lib/systemd/system/rescue.target"
"/lib/systemd/system/sys-kernel-config.mount"
"/lib/systemd/system/initrd-root-fs.target"
"/lib/systemd/system/getty.target"
"/lib/systemd/system/bluetooth.target"
"/lib/systemd/system/var-lib-machines.mount"
"/lib/systemd/system/systemd-user-sessions.service"
"/lib/systemd/system/dev-hugepages.mount"
"/lib/systemd/system/systemd-timesyncd.service"
"/lib/systemd/system/systemd-journald-dev-log.socket"
"/lib/systemd/system/sigpwr.target"
"/lib/systemd/system/systemd-halt.service"
"/lib/systemd/system/systemd-fsck-root.service"
"/lib/systemd/system/local-fs.target"
"/lib/systemd/system/printer.target"
"/lib/systemd/system/rc-local.service"
"/lib/systemd/system/initrd-fs.target"
"/lib/systemd/system/runlevel2.target"
"/lib/systemd/system/multi-user.target"
"/lib/systemd/system/systemd-hwdb-update.service"
"/lib/systemd/system/systemd-hibernate-resume@.service"
"/lib/systemd/system/systemd-hybrid-sleep.service"
"/lib/systemd/system/ldconfig.service"
"/lib/systemd/system/systemd-reboot.service"
"/lib/systemd/system/remote-fs-pre.target"
"/lib/systemd/system/kexec.target"
"/lib/systemd/system/container-getty@.service"
"/lib/systemd/system/emergency.service"
"/lib/systemd/system/busnames.target"
"/lib/systemd/system/reboot.target.wants/systemd-update-utmp-runlevel.service"
"/lib/systemd/system/rescue.target.wants/systemd-update-utmp-runlevel.service"
"/lib/systemd/system/timers.target.wants/systemd-tmpfiles-clean.timer"
"/lib/systemd/system/poweroff.target.wants/systemd-update-utmp-runlevel.service"
"/lib/systemd/system/busnames.target.wants/org.freedesktop.login1.busname"
"/lib/systemd/system/busnames.target.wants/org.freedesktop.timedate1.busname"
"/lib/systemd/system/busnames.target.wants/org.freedesktop.systemd1.busname"
"/lib/systemd/system/multi-user.target.wants/systemd-ask-password-wall.path"
"/lib/systemd/system/multi-user.target.wants/systemd-update-utmp-runlevel.service"
"/lib/systemd/system/multi-user.target.wants/systemd-logind.service"
"/lib/systemd/system/multi-user.target.wants/getty.target"
"/lib/systemd/system/multi-user.target.wants/systemd-user-sessions.service"
"/lib/systemd/system/local-fs.target.wants/tmp.mount"
"/lib/systemd/system/local-fs.target.wants/systemd-remount-fs.service"
"/lib/systemd/system/local-fs.target.wants/var-lib-machines.mount"
"/lib/systemd/system/sockets.target.wants/systemd-journald-audit.socket"
"/lib/systemd/system/sockets.target.wants/systemd-journald.socket"
"/lib/systemd/system/sockets.target.wants/systemd-initctl.socket"
"/lib/systemd/system/sockets.target.wants/systemd-coredump.socket"
"/lib/systemd/system/sockets.target.wants/systemd-journald-dev-log.socket"
"/lib/systemd/system/sysinit.target.wants/systemd-journald.service"
"/lib/systemd/system/sysinit.target.wants/dev-mqueue.mount"
"/lib/systemd/system/sysinit.target.wants/systemd-update-utmp.service"
"/lib/systemd/system/sysinit.target.wants/systemd-tmpfiles-setup.service"
"/lib/systemd/system/sysinit.target.wants/systemd-update-done.service"
"/lib/systemd/system/sysinit.target.wants/sys-kernel-debug.mount"
"/lib/systemd/system/sysinit.target.wants/systemd-ask-password-console.path"
"/lib/systemd/system/sysinit.target.wants/systemd-journal-flush.service"
"/lib/systemd/system/sysinit.target.wants/systemd-sysctl.service"
"/lib/systemd/system/sysinit.target.wants/systemd-tmpfiles-setup-dev.service"
"/lib/systemd/system/sysinit.target.wants/systemd-machine-id-commit.service"
"/lib/systemd/system/sysinit.target.wants/systemd-firstboot.service"
"/lib/systemd/system/sysinit.target.wants/sys-fs-fuse-connections.mount"
"/lib/systemd/system/sysinit.target.wants/systemd-random-seed.service"
"/lib/systemd/system/sysinit.target.wants/systemd-vconsole-setup.service"
"/lib/systemd/system/sysinit.target.wants/systemd-journal-catalog-update.service"
"/lib/systemd/system/sysinit.target.wants/sys-kernel-config.mount"
"/lib/systemd/system/sysinit.target.wants/dev-hugepages.mount"
"/lib/systemd/system/sysinit.target.wants/ldconfig.service"
"/lib/systemd/system/graphical.target.wants/systemd-update-utmp-runlevel.service"
"/lib/systemd/system-preset/90-systemd.preset"
"/lib/systemd/system-generators/systemd-debug-generator"
"/lib/systemd/system-generators/systemd-sysv-generator"
"/lib/systemd/system-generators/systemd-system-update-generator"
"/lib/systemd/system-generators/systemd-gpt-auto-generator"
"/lib/systemd/system-generators/systemd-fstab-generator"
"/lib/systemd/system-generators/systemd-dbus1-generator"
"/lib/systemd/system-generators/systemd-hibernate-resume-generator"
"/lib/systemd/system-generators/systemd-rc-local-generator"
"/lib/systemd/system-generators/systemd-getty-generator"
"/lib/security/pam_systemd.so"
%dir "/var/volatile"
%dir "/var/lib"
"/var/log"
%dir "/var/volatile/log"
%dir "/var/volatile/log/journal"
%dir "/var/lib/systemd"
"/bin/systemd-tmpfiles"
"/bin/journalctl"
"/bin/systemd-notify"
"/bin/systemd-machine-id-setup"
"/bin/systemd-ask-password"
"/bin/systemd-inhibit"
"/bin/systemd-escape"
"/bin/systemd-tty-ask-password-agent"
"/bin/systemd-firstboot"
"/bin/loginctl"
"/bin/systemctl"
%dir "/usr/share"
%dir "/usr/lib"
%dir "/usr/bin"
%dir "/usr/share/polkit-1"
%dir "/usr/share/dbus-1"
%dir "/usr/share/factory"
%dir "/usr/share/polkit-1/actions"
"/usr/share/polkit-1/actions/org.freedesktop.systemd1.policy"
"/usr/share/polkit-1/actions/org.freedesktop.timedate1.policy"
"/usr/share/polkit-1/actions/org.freedesktop.login1.policy"
%dir "/usr/share/dbus-1/services"
%dir "/usr/share/dbus-1/system-services"
"/usr/share/dbus-1/services/org.freedesktop.systemd1.service"
"/usr/share/dbus-1/system-services/org.freedesktop.systemd1.service"
"/usr/share/dbus-1/system-services/org.freedesktop.login1.service"
"/usr/share/dbus-1/system-services/org.freedesktop.timedate1.service"
%dir "/usr/share/factory/etc"
%dir "/usr/share/factory/etc/pam.d"
"/usr/share/factory/etc/nsswitch.conf"
"/usr/share/factory/etc/pam.d/other"
"/usr/share/factory/etc/pam.d/system-auth"
%dir "/usr/lib/tmpfiles.d"
%dir "/usr/lib/modules-load.d"
%dir "/usr/lib/sysctl.d"
%dir "/usr/lib/systemd"
"/usr/lib/tmpfiles.d/systemd-nspawn.conf"
"/usr/lib/tmpfiles.d/x11.conf"
"/usr/lib/tmpfiles.d/systemd-nologin.conf"
"/usr/lib/tmpfiles.d/journal-nocow.conf"
"/usr/lib/tmpfiles.d/home.conf"
"/usr/lib/tmpfiles.d/var.conf"
"/usr/lib/tmpfiles.d/legacy.conf"
"/usr/lib/tmpfiles.d/tmp.conf"
"/usr/lib/tmpfiles.d/etc.conf"
"/usr/lib/tmpfiles.d/systemd.conf"
"/usr/lib/sysctl.d/50-coredump.conf"
"/usr/lib/sysctl.d/50-default.conf"
%dir "/usr/lib/systemd/network"
%dir "/usr/lib/systemd/user-generators"
%dir "/usr/lib/systemd/user"
%dir "/usr/lib/systemd/catalog"
"/usr/lib/systemd/user-generators/systemd-dbus1-generator"
"/usr/lib/systemd/user/exit.target"
"/usr/lib/systemd/user/systemd-exit.service"
"/usr/lib/systemd/user/sockets.target"
"/usr/lib/systemd/user/default.target"
"/usr/lib/systemd/user/timers.target"
"/usr/lib/systemd/user/smartcard.target"
"/usr/lib/systemd/user/paths.target"
"/usr/lib/systemd/user/sound.target"
"/usr/lib/systemd/user/basic.target"
"/usr/lib/systemd/user/shutdown.target"
"/usr/lib/systemd/user/bluetooth.target"
"/usr/lib/systemd/user/printer.target"
"/usr/lib/systemd/user/busnames.target"
"/usr/lib/systemd/catalog/systemd.be.catalog"
"/usr/lib/systemd/catalog/systemd.fr.catalog"
"/usr/lib/systemd/catalog/systemd.catalog"
"/usr/lib/systemd/catalog/systemd.zh_TW.catalog"
"/usr/lib/systemd/catalog/systemd.pt_BR.catalog"
"/usr/lib/systemd/catalog/systemd.ru.catalog"
"/usr/lib/systemd/catalog/systemd.pl.catalog"
"/usr/lib/systemd/catalog/systemd.zh_CN.catalog"
"/usr/lib/systemd/catalog/systemd.it.catalog"
"/usr/lib/systemd/catalog/systemd.be@latin.catalog"
"/usr/bin/busctl"
"/usr/bin/systemd-cgtop"
"/usr/bin/systemd-socket-activate"
"/usr/bin/systemd-stdio-bridge"
"/usr/bin/systemd-path"
"/usr/bin/systemd-cat"
"/usr/bin/systemd-delta"
"/usr/bin/timedatectl"
"/usr/bin/systemd-cgls"
"/usr/bin/coredumpctl"
"/usr/bin/systemd-detect-virt"
"/usr/bin/systemd-nspawn"
"/usr/bin/systemd-analyze"
"/usr/bin/systemd-run"

%files -n udev
%defattr(-,-,-,-)
%dir "/sbin"
%dir "/etc"
%dir "/lib"
%dir "/bin"
%dir "/usr"
"/sbin/udevd"
%dir "/etc/udev"
%dir "/etc/udev/rules.d"
"/etc/udev/udev.conf"
"/etc/udev/rules.d/expand-fs-to-whole-partition-eMMC.rules"
"/etc/udev/rules.d/touchscreen.rules"
%dir "/lib/udev"
%dir "/lib/systemd"
%dir "/lib/udev/rules.d"
"/lib/udev/v4l_id"
"/lib/udev/cdrom_id"
"/lib/udev/collect"
"/lib/udev/ata_id"
"/lib/udev/mtd_probe"
"/lib/udev/scsi_id"
"/lib/udev/rules.d/60-evdev.rules"
"/lib/udev/rules.d/64-btrfs.rules"
"/lib/udev/rules.d/60-persistent-storage-tape.rules"
"/lib/udev/rules.d/90-vconsole.rules"
"/lib/udev/rules.d/60-block.rules"
"/lib/udev/rules.d/75-probe_mtd.rules"
"/lib/udev/rules.d/60-persistent-v4l.rules"
"/lib/udev/rules.d/75-net-description.rules"
"/lib/udev/rules.d/71-seat.rules"
"/lib/udev/rules.d/78-sound-card.rules"
"/lib/udev/rules.d/50-udev-default.rules"
"/lib/udev/rules.d/60-persistent-input.rules"
"/lib/udev/rules.d/60-drm.rules"
"/lib/udev/rules.d/80-net-setup-link.rules"
"/lib/udev/rules.d/70-uaccess.rules"
"/lib/udev/rules.d/70-power-switch.rules"
"/lib/udev/rules.d/99-systemd.rules"
"/lib/udev/rules.d/70-mouse.rules"
"/lib/udev/rules.d/60-persistent-storage.rules"
"/lib/udev/rules.d/50-firmware.rules"
"/lib/udev/rules.d/60-serial.rules"
"/lib/udev/rules.d/73-seat-late.rules"
"/lib/udev/rules.d/60-persistent-alsa.rules"
"/lib/udev/rules.d/60-cdrom_id.rules"
%dir "/lib/systemd/system"
"/lib/systemd/systemd-udevd"
%dir "/lib/systemd/system/sockets.target.wants"
%dir "/lib/systemd/system/sysinit.target.wants"
"/lib/systemd/system/initrd-udevadm-cleanup-db.service"
"/lib/systemd/system/systemd-udev-trigger.service"
"/lib/systemd/system/systemd-udevd-kernel.socket"
"/lib/systemd/system/systemd-udevd.service"
"/lib/systemd/system/systemd-udev-settle.service"
"/lib/systemd/system/systemd-udevd-control.socket"
"/lib/systemd/system/sockets.target.wants/systemd-udevd-kernel.socket"
"/lib/systemd/system/sockets.target.wants/systemd-udevd-control.socket"
"/lib/systemd/system/sysinit.target.wants/systemd-udev-trigger.service"
"/lib/systemd/system/sysinit.target.wants/systemd-udevd.service"
"/bin/udevadm"
%dir "/usr/share"
%dir "/usr/share/bash-completion"
%dir "/usr/share/bash-completion/completions"
"/usr/share/bash-completion/completions/udevadm"

%files -n systemd-initramfs
%defattr(-,-,-,-)
"/init"

%files -n systemd-kernel-install
%defattr(-,-,-,-)
%dir "/etc"
%dir "/usr"
%dir "/etc/kernel"
%dir "/etc/kernel/install.d"
%dir "/usr/lib"
%dir "/usr/bin"
%dir "/usr/lib/kernel"
%dir "/usr/lib/kernel/install.d"
"/usr/lib/kernel/install.d/50-depmod.install"
"/usr/lib/kernel/install.d/90-loaderentry.install"
"/usr/bin/kernel-install"

%files -n systemd-rpm-macros
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/lib"
%dir "/usr/lib/rpm"
%dir "/usr/lib/rpm/macros.d"
"/usr/lib/rpm/macros.d/macros.systemd"

%files -n systemd-binfmt
%defattr(-,-,-,-)
%dir "/etc"
%dir "/lib"
%dir "/usr"
%dir "/etc/binfmt.d"
%dir "/lib/systemd"
%dir "/lib/systemd/system"
"/lib/systemd/systemd-binfmt"
"/lib/systemd/system/systemd-binfmt.service"
"/lib/systemd/system/proc-sys-fs-binfmt_misc.automount"
"/lib/systemd/system/proc-sys-fs-binfmt_misc.mount"
%dir "/usr/lib"
%dir "/usr/lib/binfmt.d"

%files -n systemd-zsh-completion
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/zsh"
%dir "/usr/share/zsh/site-functions"
"/usr/share/zsh/site-functions/_sd_unit_files"
"/usr/share/zsh/site-functions/_sd_outputmodes"
"/usr/share/zsh/site-functions/_journalctl"
"/usr/share/zsh/site-functions/_busctl"
"/usr/share/zsh/site-functions/_systemd-delta"
"/usr/share/zsh/site-functions/_systemd-run"
"/usr/share/zsh/site-functions/_kernel-install"
"/usr/share/zsh/site-functions/_systemd-analyze"
"/usr/share/zsh/site-functions/_systemctl"
"/usr/share/zsh/site-functions/_loginctl"
"/usr/share/zsh/site-functions/_systemd-nspawn"
"/usr/share/zsh/site-functions/_systemd-tmpfiles"
"/usr/share/zsh/site-functions/_systemd-inhibit"
"/usr/share/zsh/site-functions/_coredumpctl"
"/usr/share/zsh/site-functions/_timedatectl"
"/usr/share/zsh/site-functions/_sd_hosts_or_user_at_host"
"/usr/share/zsh/site-functions/_udevadm"
"/usr/share/zsh/site-functions/_systemd"

%files -n systemd-xorg-xinitrc
%defattr(-,-,-,-)
%dir "/etc"
%dir "/etc/X11"
%dir "/etc/X11/xinit"
%dir "/etc/X11/xinit/xinitrc.d"
"/etc/X11/xinit/xinitrc.d/50-systemd-user.sh"

%files -n systemd-dbg
%defattr(-,-,-,-)
%dir "/lib"
%dir "/bin"
%dir "/usr"
%dir "/lib/.debug"
%dir "/lib/udev"
%dir "/lib/systemd"
%dir "/lib/security"
"/lib/.debug/libudev.so.1.6.4"
"/lib/.debug/libsystemd.so.0.14.0"
%dir "/lib/udev/.debug"
"/lib/udev/.debug/v4l_id"
"/lib/udev/.debug/cdrom_id"
"/lib/udev/.debug/collect"
"/lib/udev/.debug/ata_id"
"/lib/udev/.debug/mtd_probe"
"/lib/udev/.debug/scsi_id"
%dir "/lib/systemd/.debug"
%dir "/lib/systemd/system-generators"
"/lib/systemd/.debug/systemd-socket-proxyd"
"/lib/systemd/.debug/systemd-update-done"
"/lib/systemd/.debug/systemd-timedated"
"/lib/systemd/.debug/systemd-udevd"
"/lib/systemd/.debug/systemd-journald"
"/lib/systemd/.debug/systemd-coredump"
"/lib/systemd/.debug/systemd-sleep"
"/lib/systemd/.debug/systemd-user-sessions"
"/lib/systemd/.debug/systemd-reply-password"
"/lib/systemd/.debug/systemd-timesyncd"
"/lib/systemd/.debug/systemd-cgroups-agent"
"/lib/systemd/.debug/systemd-vconsole-setup"
"/lib/systemd/.debug/systemd-fsck"
"/lib/systemd/.debug/systemd-hibernate-resume"
"/lib/systemd/.debug/systemd-update-utmp"
"/lib/systemd/.debug/systemd"
"/lib/systemd/.debug/systemd-binfmt"
"/lib/systemd/.debug/systemd-remount-fs"
"/lib/systemd/.debug/systemd-shutdown"
"/lib/systemd/.debug/systemd-initctl"
"/lib/systemd/.debug/systemd-sysctl"
"/lib/systemd/.debug/systemd-random-seed"
"/lib/systemd/.debug/systemd-ac-power"
"/lib/systemd/.debug/systemd-logind"
%dir "/lib/systemd/system-generators/.debug"
"/lib/systemd/system-generators/.debug/systemd-debug-generator"
"/lib/systemd/system-generators/.debug/systemd-sysv-generator"
"/lib/systemd/system-generators/.debug/systemd-system-update-generator"
"/lib/systemd/system-generators/.debug/systemd-gpt-auto-generator"
"/lib/systemd/system-generators/.debug/systemd-fstab-generator"
"/lib/systemd/system-generators/.debug/systemd-dbus1-generator"
"/lib/systemd/system-generators/.debug/systemd-hibernate-resume-generator"
"/lib/systemd/system-generators/.debug/systemd-rc-local-generator"
"/lib/systemd/system-generators/.debug/systemd-getty-generator"
%dir "/lib/security/.debug"
"/lib/security/.debug/pam_systemd.so"
%dir "/bin/.debug"
"/bin/.debug/systemd-tmpfiles"
"/bin/.debug/journalctl"
"/bin/.debug/systemd-notify"
"/bin/.debug/systemd-machine-id-setup"
"/bin/.debug/systemd-ask-password"
"/bin/.debug/systemd-inhibit"
"/bin/.debug/systemd-escape"
"/bin/.debug/systemd-tty-ask-password-agent"
"/bin/.debug/systemd-firstboot"
"/bin/.debug/loginctl"
"/bin/.debug/udevadm"
"/bin/.debug/systemctl"
%dir "/usr/src"
%dir "/usr/bin"
%dir "/usr/src/debug"
%dir "/usr/src/debug/systemd"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/build"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/login"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/shared"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-hwdb"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-daemon"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-id128"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-device"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-event"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-login"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-hwdb/hwdb-internal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-hwdb/sd-hwdb.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-daemon/sd-daemon.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/sd-bus.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-control.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-type.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-introspect.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/kdbus.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-match.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-kernel.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-message.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-message.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-socket.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-internal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-match.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-signature.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-slot.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-internal.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-introspect.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-common-errors.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-creds.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-error.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-container.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-bloom.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-track.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-common-errors.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-gvariant.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-convenience.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-kernel.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-protocol.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-objects.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-creds.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-bus/bus-error.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-id128/sd-id128.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-device/device-internal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-device/device-private.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-device/sd-device.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-device/device-enumerator.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-event/sd-event.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libsystemd/sd-login/sd-login.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/login/pam_systemd.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/journal-send.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/catalog.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/journal-internal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/journal-def.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/mmap-cache.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/lookup3.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/lookup3.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/journal-file.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/journal-file.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/sd-journal.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/journal/mmap-cache.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-id128.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-bus-vtable.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-event.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-journal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-device.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-login.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-hwdb.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/systemd/sd-bus.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-hwdb.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-queue.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-device-internal.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-device-private.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-enumerate.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-monitor.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-device.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-list.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev-private.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/libudev/libudev.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/stat-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/signal-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/missing.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/alloc-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/string-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/fs-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hostname-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/utf8.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/fd-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/socket-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/device-nodes.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/parse-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/MurmurHash2.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/strv.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/siphash24.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/umask-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/fileio.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/strxcpyx.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/bus-label.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/time-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/dirent-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/mount-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/escape.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/sparse-endian.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/stat-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/virt.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/bus-label.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/terminal-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/alloc-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/audit-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hashmap.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/replace-var.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hexdecoct.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hash-funcs.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/chattr-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/random-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/socket-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/syslog-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/prioq.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/fd-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/mempool.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/selinux-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/log.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/parse-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/path-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/mempool.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/unit-name.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/user-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/login-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/errno-list.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/strv.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/escape.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/io-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/unaligned.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/prioq.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/fs-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/extract-word.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/string-table.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/siphash24.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/proc-cmdline.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/process-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/memfd-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/btrfs-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/io-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/login-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/capability-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/string-util.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/unit-name.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/time-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/sigbus.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/xattr-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/macro.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/set.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/refcnt.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hashmap.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/extract-word.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/cgroup-util.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/basic/hash-funcs.c"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/git/src/shared/bus-util.c"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/build/src"
%dir "/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/build/src/basic"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/build/src/basic/errno-to-name.h"
"/usr/src/debug/systemd/1_301+gitAUTOINC+714c62b463-r0/build/src/basic/errno-from-name.h"
%dir "/usr/bin/.debug"
"/usr/bin/.debug/busctl"
"/usr/bin/.debug/systemd-cgtop"
"/usr/bin/.debug/systemd-socket-activate"
"/usr/bin/.debug/systemd-stdio-bridge"
"/usr/bin/.debug/systemd-path"
"/usr/bin/.debug/systemd-cat"
"/usr/bin/.debug/systemd-delta"
"/usr/bin/.debug/timedatectl"
"/usr/bin/.debug/systemd-cgls"
"/usr/bin/.debug/coredumpctl"
"/usr/bin/.debug/systemd-detect-virt"
"/usr/bin/.debug/systemd-nspawn"
"/usr/bin/.debug/systemd-analyze"
"/usr/bin/.debug/systemd-run"

%files -n systemd-dev
%defattr(-,-,-,-)
%dir "/lib"
%dir "/usr"
%dir "/lib/security"
"/lib/security/pam_systemd.la"
%dir "/usr/share"
%dir "/usr/lib"
%dir "/usr/include"
%dir "/usr/share/pkgconfig"
"/usr/share/pkgconfig/systemd.pc"
"/usr/share/pkgconfig/udev.pc"
%dir "/usr/lib/pkgconfig"
"/usr/lib/libudev.la"
"/usr/lib/libsystemd.la"
"/usr/lib/libsystemd.so"
"/usr/lib/libudev.so"
"/usr/lib/pkgconfig/libudev.pc"
"/usr/lib/pkgconfig/libsystemd.pc"
%dir "/usr/include/systemd"
"/usr/include/libudev.h"
"/usr/include/systemd/_sd-common.h"
"/usr/include/systemd/sd-id128.h"
"/usr/include/systemd/sd-bus-vtable.h"
"/usr/include/systemd/sd-daemon.h"
"/usr/include/systemd/sd-event.h"
"/usr/include/systemd/sd-messages.h"
"/usr/include/systemd/sd-journal.h"
"/usr/include/systemd/sd-login.h"
"/usr/include/systemd/sd-bus-protocol.h"
"/usr/include/systemd/sd-bus.h"

%files -n systemd-doc
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/doc"
%dir "/usr/share/doc/systemd"
"/usr/share/doc/systemd/README"
"/usr/share/doc/systemd/CODING_STYLE"
"/usr/share/doc/systemd/NEWS"
"/usr/share/doc/systemd/LICENSE.GPL2"
"/usr/share/doc/systemd/LICENSE.LGPL2.1"
"/usr/share/doc/systemd/GVARIANT-SERIALIZATION"
"/usr/share/doc/systemd/DIFFERENCES"
"/usr/share/doc/systemd/PORTING-DBUS1"
"/usr/share/doc/systemd/DISTRO_PORTING"

%files -n systemd-bash-completion
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/bash-completion"
%dir "/usr/share/bash-completion/completions"
"/usr/share/bash-completion/completions/busctl"
"/usr/share/bash-completion/completions/journalctl"
"/usr/share/bash-completion/completions/systemd-cgtop"
"/usr/share/bash-completion/completions/systemd-path"
"/usr/share/bash-completion/completions/systemd-cat"
"/usr/share/bash-completion/completions/systemd-delta"
"/usr/share/bash-completion/completions/timedatectl"
"/usr/share/bash-completion/completions/kernel-install"
"/usr/share/bash-completion/completions/systemd-cgls"
"/usr/share/bash-completion/completions/coredumpctl"
"/usr/share/bash-completion/completions/systemd-detect-virt"
"/usr/share/bash-completion/completions/systemd-nspawn"
"/usr/share/bash-completion/completions/systemd-analyze"
"/usr/share/bash-completion/completions/loginctl"
"/usr/share/bash-completion/completions/systemd-run"
"/usr/share/bash-completion/completions/systemctl"

%files -n systemd-locale-be
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/be"
%dir "/usr/share/locale/be/LC_MESSAGES"
"/usr/share/locale/be/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-be+latin
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/be@latin"
%dir "/usr/share/locale/be@latin/LC_MESSAGES"
"/usr/share/locale/be@latin/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-da
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/da"
%dir "/usr/share/locale/da/LC_MESSAGES"
"/usr/share/locale/da/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-de
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/de"
%dir "/usr/share/locale/de/LC_MESSAGES"
"/usr/share/locale/de/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-el
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/el"
%dir "/usr/share/locale/el/LC_MESSAGES"
"/usr/share/locale/el/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-es
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/es"
%dir "/usr/share/locale/es/LC_MESSAGES"
"/usr/share/locale/es/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-fr
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/fr"
%dir "/usr/share/locale/fr/LC_MESSAGES"
"/usr/share/locale/fr/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-gl
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/gl"
%dir "/usr/share/locale/gl/LC_MESSAGES"
"/usr/share/locale/gl/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-hu
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/hu"
%dir "/usr/share/locale/hu/LC_MESSAGES"
"/usr/share/locale/hu/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-it
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/it"
%dir "/usr/share/locale/it/LC_MESSAGES"
"/usr/share/locale/it/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-ko
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/ko"
%dir "/usr/share/locale/ko/LC_MESSAGES"
"/usr/share/locale/ko/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-pl
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/pl"
%dir "/usr/share/locale/pl/LC_MESSAGES"
"/usr/share/locale/pl/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-pt-br
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/pt_BR"
%dir "/usr/share/locale/pt_BR/LC_MESSAGES"
"/usr/share/locale/pt_BR/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-ru
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/ru"
%dir "/usr/share/locale/ru/LC_MESSAGES"
"/usr/share/locale/ru/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-sr
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/sr"
%dir "/usr/share/locale/sr/LC_MESSAGES"
"/usr/share/locale/sr/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-sv
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/sv"
%dir "/usr/share/locale/sv/LC_MESSAGES"
"/usr/share/locale/sv/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-tr
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/tr"
%dir "/usr/share/locale/tr/LC_MESSAGES"
"/usr/share/locale/tr/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-uk
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/uk"
%dir "/usr/share/locale/uk/LC_MESSAGES"
"/usr/share/locale/uk/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-zh-cn
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/zh_CN"
%dir "/usr/share/locale/zh_CN/LC_MESSAGES"
"/usr/share/locale/zh_CN/LC_MESSAGES/systemd.mo"

%files -n systemd-locale-zh-tw
%defattr(-,-,-,-)
%dir "/usr"
%dir "/usr/share"
%dir "/usr/share/locale"
%dir "/usr/share/locale/zh_TW"
%dir "/usr/share/locale/zh_TW/LC_MESSAGES"
"/usr/share/locale/zh_TW/LC_MESSAGES/systemd.mo"

%files -n libsystemd0
%defattr(-,-,-,-)
%dir "/lib"
"/lib/libsystemd.so.0"
"/lib/libsystemd.so.0.14.0"

%files -n libudev1
%defattr(-,-,-,-)
%dir "/lib"
"/lib/libudev.so.1"
"/lib/libudev.so.1.6.4"

