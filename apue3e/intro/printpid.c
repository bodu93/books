#include "../include/apue3e.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("hello world from process ID %ld\n", (long)getpid());
	exit(0);
}
