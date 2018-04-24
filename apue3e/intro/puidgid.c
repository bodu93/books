#include "../include/apue.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
