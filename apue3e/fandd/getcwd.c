#include "../include/apue.h"
#include <unistd.h>

int main() {
	char* ptr;
	size_t size;

	if (chdir("/Users/bodu/codes/lab/apue3e/fandd/foo/testdir/bar") < 0)
		err_sys("chidr failed");

	ptr = path_alloc(&size);
	if (getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");

	printf("cwd = %s\n", ptr);

	exit(0);
}
