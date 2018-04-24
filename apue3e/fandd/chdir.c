#include "../include/apue.h"
#include <unistd.h>

int main() {
	if (chdir("/tmp") < 0)
		err_sys("chdir failed");
	printf("chdir to /tmp successed\n");
	exit(0);
}
