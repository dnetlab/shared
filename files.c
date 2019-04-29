
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "shared.h"

int file_lock(char *tag)
{
	char fn[64];
	struct flock fl;
	int fd_lock = -1;
	pid_t ppid, fpid;

	snprintf(fn, sizeof(fn), "/var/lock/%s.lock", tag);
	if ((fd_lock = open(fn, O_CREAT | O_RDWR, 0666)) < 0)
		return -1;

	fpid = 0;
	ppid = getpid();

	if (read(fd_lock, &fpid, sizeof(fpid))) {
		if (ppid == fpid) {
			// don't close the file here as that will release all locks
			return -1;
		}
	}

	memset(&fl, 0, sizeof(fl));
	fl.l_type = F_WRLCK;
	fl.l_pid = ppid;

	if (fcntl(fd_lock, F_SETLKW, &fl) < 0) {
		close(fd_lock);
		return -1;
	}

	lseek(fd_lock, 0, SEEK_SET);
	write(fd_lock, &ppid, sizeof(ppid));

	return fd_lock;
}

void file_unlock(int fd_lock)
{
	if (fd_lock >= 0) {
		ftruncate(fd_lock, 0);
		close(fd_lock);
	}
}

