/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Canonical host string. */
#define CANONICAL_HOST "arm-poky-linux-gnueabi"

/* Default DNSSEC mode */
#define DEFAULT_DNSSEC_MODE DNSSEC_ALLOW_DOWNGRADE

/* Default DNS Servers */
#define DNS_SERVERS "8.8.8.8 8.8.4.4 2001:4860:4860::8888 2001:4860:4860::8844"

/* Define if hashmap debugging is to be enabled */
/* #undef ENABLE_DEBUG_HASHMAP */

/* Define if mmap cache debugging is to be enabled */
/* #undef ENABLE_DEBUG_MMAP_CACHE */

/* Define if EFI support is to be enabled */
/* #undef ENABLE_EFI */

/* Define if kdbus is to be connected to by default */
#define ENABLE_KDBUS 1

/* Define if networkd support is to be enabled */
/* #undef ENABLE_NETWORKD */

/* Define if PolicyKit support is to be enabled */
#define ENABLE_POLKIT 1

/* Define if the ACL for wheel group should be enabled */
#define ENABLE_WHEEL_GROUP 1

/* systemd */
#define GETTEXT_PACKAGE "systemd"

/* ACL available */
/* #undef HAVE_ACL */

/* Define to 1 if you have the <acl/libacl.h> header file. */
/* #undef HAVE_ACL_LIBACL_H */

/* Define if AppArmor is available */
/* #undef HAVE_APPARMOR */

/* Define to 1 if you have the <arpa/inet.h> header file. */
/* #undef HAVE_ARPA_INET_H */

/* AUDIT available */
/* #undef HAVE_AUDIT */

/* Define if blkid is available */
#define HAVE_BLKID 1

/* Define if BZIP2 is available */
#define HAVE_BZIP2 1

/* Define to 1 if you have the <bzlib.h> header file. */
#define HAVE_BZLIB_H 1

/* Define to 1 if the system has the type `char16_t'. */
#define HAVE_CHAR16_T 1

/* Define to 1 if the system has the type `char32_t'. */
#define HAVE_CHAR32_T 1

/* Define if dbus-1 library is available */
/* #undef HAVE_DBUS */

/* Define to 1 if you have the declaration of `getrandom', and to 0 if you
   don't. */
#define HAVE_DECL_GETRANDOM 0

/* Define to 1 if you have the declaration of `gettid', and to 0 if you don't.
   */
#define HAVE_DECL_GETTID 0

/* Define to 1 if you have the declaration of `IFA_FLAGS', and to 0 if you
   don't. */
#define HAVE_DECL_IFA_FLAGS 1

/* Define to 1 if you have the declaration of `IFLA_BOND_AD_INFO', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_BOND_AD_INFO 1

/* Define to 1 if you have the declaration of `IFLA_BRIDGE_VLAN_INFO', and to
   0 if you don't. */
#define HAVE_DECL_IFLA_BRIDGE_VLAN_INFO 1

/* Define to 1 if you have the declaration of `IFLA_BRPORT_LEARNING_SYNC', and
   to 0 if you don't. */
#define HAVE_DECL_IFLA_BRPORT_LEARNING_SYNC 1

/* Define to 1 if you have the declaration of `IFLA_BR_PRIORITY', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_BR_PRIORITY 1

/* Define to 1 if you have the declaration of `IFLA_GRE_ENCAP_DPORT', and to 0
   if you don't. */
#define HAVE_DECL_IFLA_GRE_ENCAP_DPORT 1

/* Define to 1 if you have the declaration of `IFLA_INET6_ADDR_GEN_MODE', and
   to 0 if you don't. */
#define HAVE_DECL_IFLA_INET6_ADDR_GEN_MODE 1

/* Define to 1 if you have the declaration of `IFLA_IPTUN_ENCAP_DPORT', and to
   0 if you don't. */
#define HAVE_DECL_IFLA_IPTUN_ENCAP_DPORT 1

/* Define to 1 if you have the declaration of `IFLA_IPVLAN_MODE', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_IPVLAN_MODE 1

/* Define to 1 if you have the declaration of `IFLA_MACVLAN_FLAGS', and to 0
   if you don't. */
#define HAVE_DECL_IFLA_MACVLAN_FLAGS 1

/* Define to 1 if you have the declaration of `IFLA_PHYS_PORT_ID', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_PHYS_PORT_ID 1

/* Define to 1 if you have the declaration of `IFLA_VLAN_PROTOCOL', and to 0
   if you don't. */
#define HAVE_DECL_IFLA_VLAN_PROTOCOL 1

/* Define to 1 if you have the declaration of `IFLA_VTI_REMOTE', and to 0 if
   you don't. */
#define HAVE_DECL_IFLA_VTI_REMOTE 1

/* Define to 1 if you have the declaration of `IFLA_VXLAN_REMCSUM_NOPARTIAL',
   and to 0 if you don't. */
#define HAVE_DECL_IFLA_VXLAN_REMCSUM_NOPARTIAL 1

/* Define to 1 if you have the declaration of `kcmp', and to 0 if you don't.
   */
#define HAVE_DECL_KCMP 0

/* Define to 1 if you have the declaration of `keyctl', and to 0 if you don't.
   */
#define HAVE_DECL_KEYCTL 0

/* Define to 1 if you have the declaration of `LO_FLAGS_PARTSCAN', and to 0 if
   you don't. */
#define HAVE_DECL_LO_FLAGS_PARTSCAN 1

/* Define to 1 if you have the declaration of `memfd_create', and to 0 if you
   don't. */
#define HAVE_DECL_MEMFD_CREATE 0

/* Define to 1 if you have the declaration of `name_to_handle_at', and to 0 if
   you don't. */
#define HAVE_DECL_NAME_TO_HANDLE_AT 1

/* Define to 1 if you have the declaration of `NDA_IFINDEX', and to 0 if you
   don't. */
#define HAVE_DECL_NDA_IFINDEX 1

/* Define to 1 if you have the declaration of `pivot_root', and to 0 if you
   don't. */
#define HAVE_DECL_PIVOT_ROOT 0

/* Define to 1 if you have the declaration of `renameat2', and to 0 if you
   don't. */
#define HAVE_DECL_RENAMEAT2 0

/* Define to 1 if you have the declaration of `setns', and to 0 if you don't.
   */
#define HAVE_DECL_SETNS 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* ELFUTILS available */
/* #undef HAVE_ELFUTILS */

/* Define to 1 if you have the <elfutils/libdwfl.h> header file. */
/* #undef HAVE_ELFUTILS_LIBDWFL_H */

/* Define to 1 if you have the `execvpe' function. */
#define HAVE_EXECVPE 1

/* Define to 1 if you have the <fcntl.h> header file. */
/* #undef HAVE_FCNTL_H */

/* Define if FIRMWARE is available */
#define HAVE_FIRMWARE 1

/* GCRYPT available */
/* #undef HAVE_GCRYPT */

/* Define to 1 if you have the `gethostbyaddr' function. */
/* #undef HAVE_GETHOSTBYADDR */

/* Define to 1 if you have the `gethostbyname' function. */
/* #undef HAVE_GETHOSTBYNAME */

/* Define to 1 if you have the `gettimeofday' function. */
/* #undef HAVE_GETTIMEOFDAY */

/* Define if gnuefi is available */
/* #undef HAVE_GNUEFI */

/* Define if gnutls is available */
/* #undef HAVE_GNUTLS */

/* Define if IMA is available */
#define HAVE_IMA 1

/* Importd support available */
/* #undef HAVE_IMPORTD */

/* Define to 1 if you have the `inet_ntoa' function. */
/* #undef HAVE_INET_NTOA */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if the system has the type `key_serial_t'. */
/* #undef HAVE_KEY_SERIAL_T */

/* Define if kmod is available */
/* #undef HAVE_KMOD */

/* Define to 1 if you have the <libaudit.h> header file. */
/* #undef HAVE_LIBAUDIT_H */

/* Define if libcryptsetup is available */
/* #undef HAVE_LIBCRYPTSETUP */

/* Define if libcurl is available */
/* #undef HAVE_LIBCURL */

/* Define if libidn is available */
/* #undef HAVE_LIBIDN */

/* Define if libiptc is available */
/* #undef HAVE_LIBIPTC */

/* Define if libmount is available */
#define HAVE_LIBMOUNT 1

/* Define to 1 if you have the <linux/btrfs.h> header file. */
#define HAVE_LINUX_BTRFS_H 1

/* Define to 1 if you have the <linux/memfd.h> header file. */
#define HAVE_LINUX_MEMFD_H 1

/* Logind support available */
#define HAVE_LOGIND 1

/* Define in LZ4 is available */
/* #undef HAVE_LZ4 */

/* Machined support available */
/* #undef HAVE_MACHINED */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
/* #undef HAVE_MEMSET */

/* Define if microhttpd is available */
/* #undef HAVE_MICROHTTPD */

/* Define to 1 if you have the `mkostemp' function. */
#define HAVE_MKOSTEMP 1

/* Define if %ms format is supported by *scanf. */
#define HAVE_MSFORMAT 1

/* Define to 1 if you have the <netdb.h> header file. */
/* #undef HAVE_NETDB_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
/* #undef HAVE_NETINET_IN_H */

/* Define to 1 if you have the <nss.h> header file. */
/* #undef HAVE_NSS_H */

/* PAM available */
#define HAVE_PAM 1

/* Define to 1 if you have the `posix_fallocate' function. */
#define HAVE_POSIX_FALLOCATE 1

/* Define if qrencode is available */
/* #undef HAVE_QRENCODE */

/* Define if seccomp is available */
/* #undef HAVE_SECCOMP */

/* Define to 1 if you have the `secure_getenv' function. */
#define HAVE_SECURE_GETENV 1

/* Define to 1 if you have the <security/pam_ext.h> header file. */
#define HAVE_SECURITY_PAM_EXT_H 1

/* Define to 1 if you have the <security/pam_modules.h> header file. */
#define HAVE_SECURITY_PAM_MODULES_H 1

/* Define to 1 if you have the <security/pam_modutil.h> header file. */
#define HAVE_SECURITY_PAM_MODUTIL_H 1

/* Define to 1 if you have the `select' function. */
/* #undef HAVE_SELECT */

/* Define if SELinux is available */
/* #undef HAVE_SELINUX */

/* Define if SMACK is available */
#define HAVE_SMACK 1

/* Define to 1 if you have the `socket' function. */
/* #undef HAVE_SOCKET */

/* Define if /bin, /sbin aren't symlinks into /usr */
#define HAVE_SPLIT_USR 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strcasecmp' function. */
/* #undef HAVE_STRCASECMP */

/* Define to 1 if you have the `strcspn' function. */
/* #undef HAVE_STRCSPN */

/* Define to 1 if you have the `strdup' function. */
/* #undef HAVE_STRDUP */

/* Define to 1 if you have the `strerror' function. */
/* #undef HAVE_STRERROR */

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strncasecmp' function. */
/* #undef HAVE_STRNCASECMP */

/* Define to 1 if you have the `strspn' function. */
/* #undef HAVE_STRSPN */

/* SysV init scripts and rcN.d links are supported. */
#define HAVE_SYSV_COMPAT /**/

/* Define to 1 if you have the <sys/acl.h> header file. */
/* #undef HAVE_SYS_ACL_H */

/* Define to 1 if you have the <sys/auxv.h> header file. */
/* #undef HAVE_SYS_AUXV_H */

/* Define to 1 if you have the <sys/capability.h> header file. */
#define HAVE_SYS_CAPABILITY_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
/* #undef HAVE_SYS_IOCTL_H */

/* Define to 1 if you have the <sys/select.h> header file. */
/* #undef HAVE_SYS_SELECT_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
/* #undef HAVE_SYS_SOCKET_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <uchar.h> header file. */
#define HAVE_UCHAR_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if utmp/wtmp support is enabled */
#define HAVE_UTMP 1

/* Define to 1 if you have the <valgrind/memcheck.h> header file. */
/* #undef HAVE_VALGRIND_MEMCHECK_H */

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
/* #undef HAVE_VALGRIND_VALGRIND_H */

/* Define if libxkbcommon is available */
/* #undef HAVE_XKBCOMMON */

/* Define if XZ is available */
/* #undef HAVE_XZ */

/* Define if ZLIB is available */
/* #undef HAVE_ZLIB */

/* Define to 1 if you have the `__secure_getenv' function. */
/* #undef HAVE___SECURE_GETENV */

/* Path of loadkeys */
#define KBD_LOADKEYS "/usr/bin/loadkeys"

/* Path of setfont */
#define KBD_SETFONT "/usr/bin/setfont"

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Default NTP Servers */
#define NTP_SERVERS "time1.google.com time2.google.com time3.google.com time4.google.com"

/* Name of package */
#define PACKAGE "systemd"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://github.com/systemd/systemd/issues"

/* Define to the full name of this package. */
#define PACKAGE_NAME "systemd"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "systemd 229"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "systemd"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://www.freedesktop.org/wiki/Software/systemd"

/* Define to the version of this package. */
#define PACKAGE_VERSION "229"

/* Path of /etc/rc.local script */
#define RC_LOCAL_SCRIPT_PATH_START "/etc/rc.local"

/* Path of /usr/sbin/halt.local script */
#define RC_LOCAL_SCRIPT_PATH_STOP "/usr/sbin/halt.local"

/* Define if TPM should be used to log events and extend the registers */
/* #undef SD_BOOT_LOG_TPM */

/* TPM PCR register number to use */
#define SD_TPM_PCR 8

/* Define to the type of arg 1 for `select'. */
/* #undef SELECT_TYPE_ARG1 */

/* Define to the type of args 2, 3 and 4 for `select'. */
/* #undef SELECT_TYPE_ARG234 */

/* Define to the type of arg 5 for `select'. */
/* #undef SELECT_TYPE_ARG5 */

/* The size of `dev_t', as computed by sizeof. */
#define SIZEOF_DEV_T 8

/* The size of `gid_t', as computed by sizeof. */
#define SIZEOF_GID_T 4

/* The size of `pid_t', as computed by sizeof. */
#define SIZEOF_PID_T 4

/* The size of `rlim_t', as computed by sizeof. */
#define SIZEOF_RLIM_T 8

/* The size of `time_t', as computed by sizeof. */
#define SIZEOF_TIME_T 4

/* The size of `uid_t', as computed by sizeof. */
#define SIZEOF_UID_T 4

/* Default SMACK label for executed processes */
/* #undef SMACK_DEFAULT_PROCESS_LABEL */

/* Run systemd itself with SMACK label */
/* #undef SMACK_RUN_LABEL */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Maximum System GID */
#define SYSTEM_GID_MAX 999

/* Maximum System UID */
#define SYSTEM_UID_MAX 999

/* Path to telinit */
#define TELINIT "/lib/sysvinit/telinit"

/* Time Epoch */
#define TIME_EPOCH 1536596738

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
/* #undef TIME_WITH_SYS_TIME */

/* GID of the 'tty' group */
#define TTY_GID 5

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "229"

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#define _FILE_OFFSET_BITS 64

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
