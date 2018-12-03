/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU LGPLv2.
  See the file COPYING.LIB.


  fuse-2.9.4/lib/mount.h  
  Created by 2014 by Anton Feichtmeir <Tong.Duurai@gmail.com>
   
  Derived from fuse-2.9.3/lib/mount_util.h 
  "mount.h" contains all the headers and function prototypes from its predecessor(mount_util.h)
  but also includes the Linux GCC headers used by the mount.c and mount_util.c source code files 
  along with the data structure definitions and static archives(static const struct ""  "").
  Integrating the 2 and putting the definitions in this header avoids conflicting definitions
  in source code files found in the /util and /example directories.

*/



#include "fuse_opt.h"
#include "fuse_common_compat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <asm/unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/un.h>

#ifdef __NetBSD__m
#include <mntent.h>
#include <perfuse.h>

#define MS_RDONLY 	MNT_RDONLY
#define MS_NOSUID 	MNT_NOSUID
#define MS_NODEV 	MNT_NODEV
#define MS_NOEXEC 	MNT_NOEXEC
#define MS_SYNCHRONOUS 	MNT_SYNCHRONOUS
#define MS_NOATIME 	MNT_NOATIME

#define umount2(mnt, flags) unmount(mnt, (flags == 2) ? MNT_FORCE : 0)

#endif


#define FUSERMOUNT_PROG		"fusermount"
#define FUSE_COMMFD_ENV		"_FUSE_COMMFD"

#ifndef HAVE_FORK
#define fork() vfork()
#endif

#ifndef MS_DIRSYNC
#define MS_DIRSYNC 128
#endif


enum {
	KEY_KERN_FLAG,
	KEY_KERN_OPT,
	KEY_FUSERMOUNT_OPT,
	KEY_SUBTYPE_OPT,
	KEY_MTAB_OPT,
	KEY_ALLOW_ROOT,
	KEY_RO,
	KEY_HELP,
	KEY_VERSION,
};

struct mount_opts {
	int allow_other;
	int allow_root;
	int ishelp;
	int flags;
	int nonempty;
	int auto_unmount;
	int blkdev;
	char *fsname;
	char *subtype;
	char *subtype_opt;
	char *mtab_opts;
	char *fusermount_opts;
	char *kernel_opts;
};

struct mount_flags {
	const char *opt;
	unsigned long flag;
	int on;
        int safe;
};

#define FUSE_MOUNT_OPT(t, p) { t, offsetof(struct mount_opts, p), 1 }




static const struct fuse_opt fuse_mount_opts[] = {
	FUSE_MOUNT_OPT("allow_other",		allow_other),
	FUSE_MOUNT_OPT("allow_root",		allow_root),
	FUSE_MOUNT_OPT("nonempty",		nonempty),
	FUSE_MOUNT_OPT("blkdev",		blkdev),
	FUSE_MOUNT_OPT("auto_unmount",		auto_unmount),
	FUSE_MOUNT_OPT("fsname=%s",		fsname),
	FUSE_MOUNT_OPT("subtype=%s",		subtype),
	FUSE_OPT_KEY("allow_other",		KEY_KERN_OPT),
	FUSE_OPT_KEY("allow_root",		KEY_ALLOW_ROOT),
	FUSE_OPT_KEY("nonempty",		KEY_FUSERMOUNT_OPT),
	FUSE_OPT_KEY("auto_unmount",		KEY_FUSERMOUNT_OPT),
	FUSE_OPT_KEY("blkdev",			KEY_FUSERMOUNT_OPT),
	FUSE_OPT_KEY("fsname=",			KEY_FUSERMOUNT_OPT),
	FUSE_OPT_KEY("subtype=",		KEY_SUBTYPE_OPT),
	FUSE_OPT_KEY("large_read",		KEY_KERN_OPT),
	FUSE_OPT_KEY("blksize=",		KEY_KERN_OPT),
	FUSE_OPT_KEY("default_permissions",	KEY_KERN_OPT),
	FUSE_OPT_KEY("max_read=",		KEY_KERN_OPT),
	FUSE_OPT_KEY("max_read=",		FUSE_OPT_KEY_KEEP),
	FUSE_OPT_KEY("user=",			KEY_MTAB_OPT),
	FUSE_OPT_KEY("-r",			KEY_RO),
	FUSE_OPT_KEY("ro",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("rw",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("suid",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("nosuid",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("dev",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("nodev",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("exec",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("noexec",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("async",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("sync",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("dirsync",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("atime",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("noatime",			KEY_KERN_FLAG),
	FUSE_OPT_KEY("-h",			KEY_HELP),
	FUSE_OPT_KEY("--help",			KEY_HELP),
	FUSE_OPT_KEY("-V",			KEY_VERSION),
	FUSE_OPT_KEY("--version",		KEY_VERSION),
	FUSE_OPT_END
};


static const struct mount_flags mount_flags[] = {
	{"rw",	    MS_RDONLY,	    0},
	{"ro",	    MS_RDONLY,	    1},
	{"suid",    MS_NOSUID,	    0},
	{"nosuid",  MS_NOSUID,	    1},
	{"dev",	    MS_NODEV,	    0},
	{"nodev",   MS_NODEV,	    1},
	{"exec",    MS_NOEXEC,	    0},
	{"noexec",  MS_NOEXEC,	    1},
	{"async",   MS_SYNCHRONOUS, 0},
	{"sync",    MS_SYNCHRONOUS, 1},
	{"atime",   MS_NOATIME,	    0},
	{"noatime", MS_NOATIME,	    1},
#ifndef __NetBSD__
	{"dirsync", MS_DIRSYNC,	    1},
#endif
	{NULL,	    0,		    0}
};

static void mount_help(void)
{
	fprintf(stderr,
"    -o allow_other         allow access to other users\n"
"    -o allow_root          allow access to root\n"
"    -o auto_unmount        auto unmount on process termination\n"
"    -o nonempty            allow mounts over non-empty file/dir\n"
"    -o default_permissions enable permission checking by kernel\n"
"    -o fsname=NAME         set filesystem name\n"
"    -o subtype=NAME        set filesystem type\n"
"    -o large_read          issue large read requests (2.4 only)\n"
"    -o max_read=N          set maximum size of read requests\n"
"\n");
}


int fuse_mnt_add_mount(const char *progname, const char *fsname, const char *mnt, const char *type, const char *opts);
int fuse_mnt_remove_mount(const char *progname, const char *mnt);
int fuse_mnt_umount(const char *progname, const char *abs_mnt,  const char *rel_mnt, int lazy);
char *fuse_mnt_resolve_path(const char *progname, const char *orig);
int fuse_mnt_check_empty(const char *progname, const char *mnt,
			 mode_t rootmode, off_t rootsize);
int fuse_mnt_check_fuseblk(void);
void fuse_kern_unmount(const char *mountpoint, int fd);
void fuse_unmount_compat22(const char *mountpoint);
int fuse_mount_compat22(const char *mountpoint, const char *opts);
int fuse_kern_mount(const char *mountpoint, struct fuse_args *args);














































