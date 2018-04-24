#include "../include/apue.h"

int main() {
	int c;
	// setvbuf(stdin, NULL, _IONBF, 0);
	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
