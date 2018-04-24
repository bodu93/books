#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: t_unlink <path>\n");
		exit(1);
	}

	int err = unlinkat(AT_FDCWD, argv[1], AT_REMOVEDIR);
	if (err < 0) {
		perror("unlinkat: ");
		exit(1);
	}

	exit(0);
}
