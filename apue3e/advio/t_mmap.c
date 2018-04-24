#include "../include/apue.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define COPYINCR (1024 * 1024 * 1024) /* 1 GB */

int main(int argc, char* argv[]) {
	if (argc != 3)
		err_quit("usage: %s <fromfile> <tofile>", argv[0]);

	int fdin;
	if ((fdin = open(argv[1], O_RDONLY)) < 0)
		err_sys("can't open %s for reading", argv[1]);

	int fdout;
	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
		err_sys("can't creat %s for writing", argv[2]);

	struct stat sbuf;
	if (fstat(fdin, &sbuf) < 0)
		err_sys("fstat error");

	if (ftruncate(fdout, sbuf.st_size) < 0)
		err_sys("ftruncate error");

	void* src = NULL;
	void* dst = NULL;
	off_t fsz = 0;
	size_t copysz = 0;
	while (fsz < sbuf.st_size) {
		if ((sbuf.st_size - fsz) > COPYINCR)
			copysz = COPYINCR;
		else
			copysz = sbuf.st_size - fsz;

		if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED)
			err_sys("mmap error for input");
		if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED)
			err_sys("mmap error for output");

		/* do the copy! */
		memcpy(dst, src, copysz);

		munmap(src, copysz);
		munmap(dst, copysz);

		fsz += copysz;
	}

	exit(0);
}
