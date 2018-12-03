/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU LGPLv2.
  See the file COPYING.LIB.
 
  fuse-2.9.4/lib/mount.c
  Re-Created and painstakingly debugged  2014 by Anton Feichtmeir <Tong.Duurai@gmail.com>
  /lib/mount.c combines the source code from the original mount.c along with mount_util.c to 
  avoid definition conflicts and since the functions from the original mount.c use functions 
  from the mount_util source code file.

*/

#include "mount.h"



static int mtab_needs_update(const char *mnt)
{
	int res;
	struct stat stbuf;

	/* If mtab is within new mount, don't touch it */
	if (strncmp(mnt, _PATH_MOUNTED, strlen(mnt)) == 0 &&
	    _PATH_MOUNTED[strlen(mnt)] == '/')
		return 0;

	/*
	 * Skip mtab update if /etc/mtab:
	 *
	 *  - doesn't exist,
	 *  - is a symlink,
	 *  - is on a read-only filesystem.
	 */
	res = lstat(_PATH_MOUNTED, &stbuf);
	if (res == -1) {
		if (errno == ENOENT)
			return 0;
	} else {
		uid_t ruid;
		int err;

		if (S_ISLNK(stbuf.st_mode))
			return 0;

		ruid = syscall(__NR_getuid);
		if (ruid != 0)
			setreuid(0, -1);

		res = access(_PATH_MOUNTED, W_OK);
		err = (res == -1) ? errno : 0;
		if (ruid != 0)
			setreuid(ruid, -1);

		if (err == EROFS)
			return 0;
	}

	return 1;
}


static int add_mount(const char *progname, const char *fsname,const char *mnt, const char *type, const char *opts)
{
	int res;
	int status;
	sigset_t blockmask;
	sigset_t oldmask;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGCHLD);
	res = sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	if (res == -1) {
		fprintf(stderr, "%s: sigprocmask: %s\n", progname, strerror(errno));
		return -1;
	}

	res = fork();
	if (res == -1) {
		fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
		goto out_restore;
	}
	if (res == 0) {
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
		setuid(syscall(__NR_geteuid));
		execl("/bin/mount", "/bin/mount", "--no-canonicalize", "-i",
		      "-f", "-t", type, "-o", opts, fsname, mnt, NULL);
		fprintf(stderr, "%s: failed to execute /bin/mount: %s\n",
			progname, strerror(errno));
		exit(1);
	}
	res = waitpid(res, &status, 0);
	if (res == -1)
		fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));

	if (status != 0)
		res = -1;

 out_restore:
	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	return res;
}

int fuse_mnt_add_mount(const char *progname, const char *fsname,
		       const char *mnt, const char *type, const char *opts)
{
	if (!mtab_needs_update(mnt))
		return 0;

	return add_mount(progname, fsname, mnt, type, opts);
}

static int exec_umount(const char *progname, const char *rel_mnt, int lazy)
{
	int res;
	int status;
	sigset_t blockmask;
	sigset_t oldmask;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGCHLD);
	res = sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	if (res == -1) {
		fprintf(stderr, "%s: sigprocmask: %s\n", progname, strerror(errno));
		return -1;
	}

	res = fork();
	if (res == -1) {
		fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
		goto out_restore;
	}
	if (res == 0) {
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
		setuid(syscall(__NR_geteuid));
		execl("/bin/umount", "/bin/umount", "-i", rel_mnt,
		      lazy ? "-l" : NULL, NULL);
		fprintf(stderr, "%s: failed to execute /bin/umount: %s\n",
			progname, strerror(errno));
		exit(1);
	}
	res = waitpid(res, &status, 0);
	if (res == -1)
		fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));

	if (status != 0) {
		res = -1;
	}

 out_restore:
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return res;

}

int fuse_mnt_umount(const char *progname, const char *abs_mnt,
		    const char *rel_mnt, int lazy)
{
	int res;

	if (!mtab_needs_update(abs_mnt)) {
                int lzy = lazy ? 2 : 0;
		res = syscall(__NR_umount2,rel_mnt,lzy);
		if (res == -1)
			fprintf(stderr, "%s: failed to unmount %s: %s\n",
				progname, abs_mnt, strerror(errno));
		return res;
	}

	return exec_umount(progname, rel_mnt, lazy);
}

static int remove_mount(const char *progname, const char *mnt)
{
	int res;
	int status;
	sigset_t blockmask;
	sigset_t oldmask;

	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGCHLD);
	res = sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	if (res == -1) {
		fprintf(stderr, "%s: sigprocmask: %s\n", progname, strerror(errno));
		return -1;
	}

	res = fork();
	if (res == -1) {
		fprintf(stderr, "%s: fork: %s\n", progname, strerror(errno));
		goto out_restore;
	}
	if (res == 0) {
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
		setuid(syscall(__NR_geteuid));
		execl("/bin/umount", "/bin/umount", "--no-canonicalize", "-i",
		      "--fake", mnt, NULL);
		fprintf(stderr, "%s: failed to execute /bin/umount: %s\n",
			progname, strerror(errno));
		exit(1);
	}
	res = waitpid(res, &status, 0);
	if (res == -1)
		fprintf(stderr, "%s: waitpid: %s\n", progname, strerror(errno));

	if (status != 0)
		res = -1;

 out_restore:
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return res;
}

int fuse_mnt_remove_mount(const char *progname, const char *mnt)
{
	if (!mtab_needs_update(mnt))
		return 0;

	return remove_mount(progname, mnt);
}

char *fuse_mnt_resolve_path(const char *progname, const char *orig)
{
	char buf[PATH_MAX];
	char *copy;
	char *dst;
	char *end;
	char *lastcomp;
	const char *toresolv;

	if (!orig[0]) {
		fprintf(stderr, "%s: invalid mountpoint '%s'\n", progname,
			orig);
		return NULL;
	}

	copy = strdup(orig);
	if (copy == NULL) {
		fprintf(stderr, "%s: failed to allocate memory\n", progname);
		return NULL;
	}

	toresolv = copy;
	lastcomp = NULL;
	for (end = copy + strlen(copy) - 1; end > copy && *end == '/'; end --);
	if (end[0] != '/') {
		char *tmp;
		end[1] = '\0';
		tmp = strrchr(copy, '/');
		if (tmp == NULL) {
			lastcomp = copy;
			toresolv = ".";
		} else {
			lastcomp = tmp + 1;
			if (tmp == copy)
				toresolv = "/";
		}
		if (strcmp(lastcomp, ".") == 0 || strcmp(lastcomp, "..") == 0) {
			lastcomp = NULL;
			toresolv = copy;
		}
		else if (tmp)
			tmp[0] = '\0';
	}
	if (realpath(toresolv, buf) == NULL) {
		fprintf(stderr, "%s: bad mount point %s: %s\n", progname, orig,
			strerror(errno));
		free(copy);
		return NULL;
	}
	if (lastcomp == NULL)
		dst = strdup(buf);
	else {
		dst = (char *) malloc(strlen(buf) + 1 + strlen(lastcomp) + 1);
		if (dst) {
			unsigned buflen = strlen(buf);
			if (buflen && buf[buflen-1] == '/')
				sprintf(dst, "%s%s", buf, lastcomp);
			else
				sprintf(dst, "%s/%s", buf, lastcomp);
		}
	}
	free(copy);
	if (dst == NULL)
		fprintf(stderr, "%s: failed to allocate memory\n", progname);
	return dst;
}

int fuse_mnt_check_empty(const char *progname, const char *mnt,
			 mode_t rootmode, off_t rootsize)
{
	int isempty = 1;

	if (S_ISDIR(rootmode)) {
		struct dirent *ent;
		DIR *dp = opendir(mnt);
		if (dp == NULL) {
			fprintf(stderr,
				"%s: failed to open mountpoint for reading: %s\n",
				progname, strerror(errno));
			return -1;
		}
		while ((ent = readdir(dp)) != NULL) {
			if (strcmp(ent->d_name, ".") != 0 &&
			    strcmp(ent->d_name, "..") != 0) {
				isempty = 0;
				break;
			}
		}
		closedir(dp);
	} else if (rootsize)
		isempty = 0;

	if (!isempty) {
		fprintf(stderr, "%s: mountpoint is not empty\n", progname);
		fprintf(stderr, "%s: if you are sure this is safe, use the 'nonempty' mount option\n", progname);
		return -1;
	}
	return 0;
}

int fuse_mnt_check_fuseblk(void)
{
	char buf[256];
	FILE *f = fopen("/proc/filesystems", "r");
	if (!f)
		return 1;

	while (fgets(buf, sizeof(buf), f))
		if (strstr(buf, "fuseblk\n")) {
			fclose(f);
			return 1;
		}

	fclose(f);
	return 0;
}

static void exec_fusermount(const char *argv[])
{
	execv(FUSERMOUNT_DIR "/" FUSERMOUNT_PROG, (char **) argv);
	execvp(FUSERMOUNT_PROG, (char **) argv);
}

static void mount_version(void)
{
	int pid = fork();
	if (!pid) {
		const char *argv[] = { FUSERMOUNT_PROG, "--version", NULL };
		exec_fusermount(argv);
		_exit(1);
	} else if (pid != -1)
		waitpid(pid, NULL, 0);
}



static void set_mount_flag(const char *s, int *flags)
{
	int i;

	for (i = 0; mount_flags[i].opt != NULL; i++) {
		const char *opt = mount_flags[i].opt;
		if (strcmp(opt, s) == 0) {
			if (mount_flags[i].on)
				*flags |= mount_flags[i].flag;
			else
				*flags &= ~mount_flags[i].flag;
			return;
		}
	}
	fprintf(stderr, "fuse: internal error, can't find mount flag\n");
	abort();
}

static int fuse_mount_opt_proc(void *data, const char *arg, int key,
			       struct fuse_args *outargs)
{
	struct mount_opts *mo = data;

	switch (key) {
	case KEY_ALLOW_ROOT:
		if (fuse_opt_add_opt(&mo->kernel_opts, "allow_other") == -1 ||
		    fuse_opt_add_arg(outargs, "-oallow_root") == -1)
			return -1;
		return 0;

	case KEY_RO:
		arg = "ro";
		/* fall through */
	case KEY_KERN_FLAG:
		set_mount_flag(arg, &mo->flags);
		return 0;

	case KEY_KERN_OPT:
		return fuse_opt_add_opt(&mo->kernel_opts, arg);

	case KEY_FUSERMOUNT_OPT:
		return fuse_opt_add_opt_escaped(&mo->fusermount_opts, arg);

	case KEY_SUBTYPE_OPT:
		return fuse_opt_add_opt(&mo->subtype_opt, arg);

	case KEY_MTAB_OPT:
		return fuse_opt_add_opt(&mo->mtab_opts, arg);

	case KEY_HELP:
		mount_help();
		mo->ishelp = 1;
		break;

	case KEY_VERSION:
		mount_version();
		mo->ishelp = 1;
		break;
	}
	return 1;
}

/* return value:
 * >= 0	 => fd
 * -1	 => error
 */
static int receive_fd(int fd)
{
	struct msghdr msg;
	struct iovec iov;
	char buf[1];
	int rv;
	size_t ccmsg[CMSG_SPACE(sizeof(int)) / sizeof(size_t)];
	struct cmsghdr *cmsg;

	iov.iov_base = buf;
	iov.iov_len = 1;

	memset(&msg, 0, sizeof(msg));
	msg.msg_name = 0;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	/* old BSD implementations should use msg_accrights instead of
	 * msg_control; the interface is different. */
	msg.msg_control = ccmsg;
	msg.msg_controllen = sizeof(ccmsg);

	while(((rv = recvmsg(fd, &msg, 0)) == -1) && errno == EINTR);
	if (rv == -1) {
		perror("recvmsg");
		return -1;
	}
	if(!rv) {
		/* EOF */
		return -1;
	}

	cmsg = CMSG_FIRSTHDR(&msg);
	if (!cmsg->cmsg_type == SCM_RIGHTS) {
		fprintf(stderr, "got control message of unknown type %d\n",
			cmsg->cmsg_type);
		return -1;
	}
	return *(int*)CMSG_DATA(cmsg);
}

void fuse_kern_unmount(const char *mountpoint, int fd)
{
	int res;
	int pid;

	if (!mountpoint)
		return;

	if (fd != -1) {
		struct pollfd pfd;

		pfd.fd = fd;
		pfd.events = 0;
		res = poll(&pfd, 1, 0);

		/* Need to close file descriptor, otherwise synchronous umount
		   would recurse into filesystem, and deadlock.

		   Caller expects fuse_kern_unmount to close the fd, so close it
		   anyway. */
		close(fd);

		/* If file poll returns POLLERR on the device file descriptor,
		   then the filesystem is already unmounted */
		if (res == 1 && (pfd.revents & POLLERR))
			return;
	}

	if (syscall(__NR_geteuid) == 0) {
		fuse_mnt_umount("fuse", mountpoint, mountpoint,  1);
		return;
	}

	res = syscall(__NR_umount2,mountpoint, 2);
	if (res == 0)
		return;

	pid = fork();
	if(pid == -1)
		return;

	if(pid == 0) {
		const char *argv[] = { FUSERMOUNT_PROG, "-u", "-q", "-z",
				       "--", mountpoint, NULL };

		exec_fusermount(argv);
		_exit(1);
	}
	waitpid(pid, NULL, 0);
}

void fuse_unmount_compat22(const char *mountpoint)
{
	fuse_kern_unmount(mountpoint, -1);
}

static int fuse_mount_fusermount(const char *mountpoint, struct mount_opts *mo,
		const char *opts, int quiet)
{
	int fds[2], pid;
	int res;
	int rv;

	if (!mountpoint) {
		fprintf(stderr, "fuse: missing mountpoint parameter\n");
		return -1;
	}

	res = socketpair(PF_UNIX, SOCK_STREAM, 0, fds);
	if(res == -1) {
		perror("fuse: socketpair() failed");
		return -1;
	}

	pid = fork();
	if(pid == -1) {
		perror("fuse: fork() failed");
		close(fds[0]);
		close(fds[1]);
		return -1;
	}

	if(pid == 0) {
		char env[10];
		const char *argv[32];
		int a = 0;

		if (quiet) {
			int fd = open("/dev/null", O_RDONLY);
			if (fd != -1) {
				dup2(fd, 1);
				dup2(fd, 2);
			}
		}

		argv[a++] = FUSERMOUNT_PROG;
		if (opts) {
			argv[a++] = "-o";
			argv[a++] = opts;
		}
		argv[a++] = "--";
		argv[a++] = mountpoint;
		argv[a++] = NULL;

		close(fds[1]);
		fcntl(fds[0], F_SETFD, 0);
		snprintf(env, sizeof(env), "%i", fds[0]);
		setenv(FUSE_COMMFD_ENV, env, 1);
		exec_fusermount(argv);
		perror("fuse: failed to exec fusermount");
		_exit(1);
	}

	close(fds[0]);
	rv = receive_fd(fds[1]);

	if (!mo->auto_unmount) {
		/* with auto_unmount option fusermount will not exit until 
		   this socket is closed */
		close(fds[1]);
		waitpid(pid, NULL, 0); /* bury zombie */
	}

	return rv;
}

int fuse_mount_compat22(const char *mountpoint, const char *opts)
{
	struct mount_opts mo;
	memset(&mo, 0, sizeof(mo));
	mo.flags = MS_NOSUID | MS_NODEV;

	return fuse_mount_fusermount(mountpoint, &mo, opts, 0);
}

static int fuse_mount_sys(const char *mnt, struct mount_opts *mo,
			  const char *mnt_opts)
{
	char tmp[128];
	const char *devname = "/dev/fuse";
	char *source = NULL;
	char *type = NULL;
	struct stat stbuf;
	int fd;
	int res;

	if (!mnt) {
		fprintf(stderr, "fuse: missing mountpoint parameter\n");
		return -1;
	}

	res = stat(mnt, &stbuf);
	if (res == -1) {
		fprintf(stderr ,"fuse: failed to access mountpoint %s: %s\n",
			mnt, strerror(errno));
		return -1;
	}

	if (!mo->nonempty) {
		res = fuse_mnt_check_empty("fuse", mnt, stbuf.st_mode,
					   stbuf.st_size);
		if (res == -1)
			return -1;
	}

	if (mo->auto_unmount) {
		/* Tell the caller to fallback to fusermount because
		   auto-unmount does not work otherwise. */
		return -2;
	}

	fd = open(devname, O_RDWR);
	if (fd == -1) {
		if (errno == ENODEV || errno == ENOENT)
			fprintf(stderr, "fuse: device not found, try 'modprobe fuse' first\n");
		else
			fprintf(stderr, "fuse: failed to open %s: %s\n",
				devname, strerror(errno));
		return -1;
	}

	snprintf(tmp, sizeof(tmp),  "fd=%i,rootmode=%o,user_id=%i,group_id=%i",
		 fd, stbuf.st_mode & S_IFMT, getuid(), getgid());

	res = fuse_opt_add_opt(&mo->kernel_opts, tmp);
	if (res == -1)
		goto out_close;

	source = malloc((mo->fsname ? strlen(mo->fsname) : 0) +
			(mo->subtype ? strlen(mo->subtype) : 0) +
			strlen(devname) + 32);

	type = malloc((mo->subtype ? strlen(mo->subtype) : 0) + 32);
	if (!type || !source) {
		fprintf(stderr, "fuse: failed to allocate memory\n");
		goto out_close;
	}

	strcpy(type, mo->blkdev ? "fuseblk" : "fuse");
	if (mo->subtype) {
		strcat(type, ".");
		strcat(type, mo->subtype);
	}
	strcpy(source,
	       mo->fsname ? mo->fsname : (mo->subtype ? mo->subtype : devname));

	res = mount(source, mnt, type, mo->flags, mo->kernel_opts);
	if (res == -1 && errno == ENODEV && mo->subtype) {
		/* Probably missing subtype support */
		strcpy(type, mo->blkdev ? "fuseblk" : "fuse");
		if (mo->fsname) {
			if (!mo->blkdev)
				sprintf(source, "%s#%s", mo->subtype,
					mo->fsname);
		} else {
			strcpy(source, type);
		}
		res = syscall(__NR_mount,source, mnt, type, mo->flags, mo->kernel_opts);
	}
	if (res == -1) {
		/*
		 * Maybe kernel doesn't support unprivileged mounts, in this
		 * case try falling back to fusermount
		 */
		if (errno == EPERM) {
			res = -2;
		} else {
			int errno_save = errno;
			if (mo->blkdev && errno == ENODEV &&
			    !fuse_mnt_check_fuseblk())
				fprintf(stderr,
					"fuse: 'fuseblk' support missing\n");
			else
				fprintf(stderr, "fuse: mount failed: %s\n",
					strerror(errno_save));
		}

		goto out_close;
	}

#ifndef __NetBSD__
#ifndef IGNORE_MTAB
	if (geteuid() == 0) {
		char *newmnt = fuse_mnt_resolve_path("fuse", mnt);
		res = -1;
		if (!newmnt)
			goto out_umount;

		res = fuse_mnt_add_mount("fuse", source, newmnt, type,
					 mnt_opts);
		free(newmnt);
		if (res == -1)
			goto out_umount;
	}
#endif /* IGNORE_MTAB */
#endif /* __NetBSD__ */
	free(type);
	free(source);

	return fd;

out_umount:
	umount2(mnt, 2); /* lazy umount */
out_close:
	free(type);
	free(source);
	close(fd);
	return res;
}

static int get_mnt_flag_opts(char **mnt_optsp, int flags)
{
	int i;

	if (!(flags & MS_RDONLY) && fuse_opt_add_opt(mnt_optsp, "rw") == -1)
		return -1;

	for (i = 0; mount_flags[i].opt != NULL; i++) {
		if (mount_flags[i].on && (flags & mount_flags[i].flag) &&
		    fuse_opt_add_opt(mnt_optsp, mount_flags[i].opt) == -1)
			return -1;
	}
	return 0;
}

int fuse_kern_mount(const char *mountpoint, struct fuse_args *args)
{
	struct mount_opts mo;
	int res = -1;
	char *mnt_opts = NULL;

	memset(&mo, 0, sizeof(mo));
	mo.flags = MS_NOSUID | MS_NODEV;

	if (args &&
	    fuse_opt_parse(args, &mo, fuse_mount_opts, fuse_mount_opt_proc) == -1)
		return -1;

	if (mo.allow_other && mo.allow_root) {
		fprintf(stderr, "fuse: 'allow_other' and 'allow_root' options are mutually exclusive\n");
		goto out;
	}
	res = 0;
	if (mo.ishelp)
		goto out;

	res = -1;
	if (get_mnt_flag_opts(&mnt_opts, mo.flags) == -1)
		goto out;
	if (mo.kernel_opts && fuse_opt_add_opt(&mnt_opts, mo.kernel_opts) == -1)
		goto out;
	if (mo.mtab_opts &&  fuse_opt_add_opt(&mnt_opts, mo.mtab_opts) == -1)
		goto out;

	res = fuse_mount_sys(mountpoint, &mo, mnt_opts);
	if (res == -2) {
		if (mo.fusermount_opts &&
		    fuse_opt_add_opt(&mnt_opts, mo.fusermount_opts) == -1)
			goto out;

		if (mo.subtype) {
			char *tmp_opts = NULL;

			res = -1;
			if (fuse_opt_add_opt(&tmp_opts, mnt_opts) == -1 ||
			    fuse_opt_add_opt(&tmp_opts, mo.subtype_opt) == -1) {
				free(tmp_opts);
				goto out;
			}

			res = fuse_mount_fusermount(mountpoint, &mo, tmp_opts, 1);
			free(tmp_opts);
			if (res == -1)
				res = fuse_mount_fusermount(mountpoint, &mo,
							    mnt_opts, 0);
		} else {
			res = fuse_mount_fusermount(mountpoint, &mo, mnt_opts, 0);
		}
	}
out:
	free(mnt_opts);
	free(mo.fsname);
	free(mo.subtype);
	free(mo.fusermount_opts);
	free(mo.subtype_opt);
	free(mo.kernel_opts);
	free(mo.mtab_opts);
	return res;
}

