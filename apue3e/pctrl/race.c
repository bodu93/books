#include "../include/apue.h"

#include <unistd.h>

static void charactatime(char*);

int main() {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		charactatime("output from child\n");
	} else {
		charactatime("output from parent\n");
	}

	exit(0);
}

static void
charactatime(char* name) {
	setbuf(stdout, NULL);

	int c;
	for (char* ptr = name; (c = *ptr++) != 0; )
		putc(c, stdout);
}
