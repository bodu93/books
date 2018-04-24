#include "../include/apue.h"

#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define DEF_PAGER "/usr/bin/more" /* default pager program */

int main(int argc, char* argv[]) {
	if (argc != 2)
		err_quit("usage: a.out <pathname>");

	FILE* fp;
	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
	
	int fd[2];
	if (pipe(fd) < 0)
		err_sys("pipe error");

	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {
		close(fd[0]);


		char line[MAXLINE];
		while (fgets(line, MAXLINE, fp) != NULL) {
			int n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}

		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]); /* close write end because we have written all contents in the input file */

		if (waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");
		exit(0);
	} else {
		close(fd[1]);
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd[0]);
		}

		char* pager = DEF_PAGER;
//		if ((pager = getenv("PAGER")) == NULL)
//			pager = DEF_PAGER;
//
		char* argv0;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;

		if (execl(pager, argv0, (char*)0) < 0)
			err_sys("execl error for %s", pager);
	}

	exit(0);
}
