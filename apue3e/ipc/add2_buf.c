#include "../include/apue.h"

int main() {
	char line[MAXLINE];
	//if (setvbuf(stdin, NULL, _IOLBF, 0) != 0)
	//	err_sys("setvbuf error");
	//if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
	//	err_sys("setvbuf error");
	while (fgets(line, MAXLINE, stdin) != NULL) {
		//fflush(stdin);
		int int1, int2;
		if (sscanf(line, "%d%d", &int1, &int2) == 2) {
			if (printf("%d\n", int1 + int2) == EOF)
				err_sys("printf error");
		} else {
			if (printf("invalid args\n") == EOF)
				err_sys("printf error");
		}
		fflush(stdout);
	}

	exit(0);
}
