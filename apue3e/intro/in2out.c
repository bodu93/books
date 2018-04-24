#include "../include/apue3e.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096

int main() {
	int n;
	char buf[BUFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}
