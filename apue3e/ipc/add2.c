#include "../include/apue.h"

#include <unistd.h>
#include <string.h>

int main() {
	int n;
	char line[MAXLINE];
	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
		line[n] = 0;

		int int1;
		int int2;
		if ((sscanf(line, "%d%d", &int1, &int2) == 2)) {
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				err_sys("write error");
		} else {
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
	}

	exit(0);
}
