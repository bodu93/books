#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: t_link <path1> <path2>\n");
		exit(1);
	}

	/*
	 * as man page described:
	 * As mandated by POSIX.1, path1 may not be a directory
	 * actually, on macOS, if path1 is a directory, link
	 * will failed with EPERM
	 */
	int err = link(argv[1], argv[2]);
	if (err < 0) {
		perror("link: ");
		exit(1);
	}

	exit(0);
}
