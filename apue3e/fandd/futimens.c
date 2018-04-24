#include "../include/apue.h"

#undef _POSIX_C_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	struct stat statbuf;
	// struct timespec times[2];
	time_t times[2];
	int fd;
	for (int i = 1; i < argc; i++) {
		if (stat(argv[i], &statbuf) < 0) {
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) {
			err_ret("%s: open error", argv[i]);
			continue;
		}

		times[0] = statbuf.st_atime;
		times[1] = statbuf.st_mtime;
		struct timespec tspecs[2];
		tspecs[0].tv_sec = times[0];
		tspecs[0].tv_nsec = 0;
		tspecs[1].tv_sec = times[1];
		tspecs[1].tv_nsec = 0;
		if (futimens(fd, tspecs) < 0)
			err_ret("%s: futimens error", argv[i]);
		close(fd);
	}

	exit(0);
}
