#include "../include/apue.h"

#include <signal.h>
#include <unistd.h>
#include <string.h>


static void sig_pipe(int);

int main() {
	/* write end which reader end closed will cause this signal */
	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	int fd1[2], fd2[2];
	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	pid_t pid;
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {
		close(fd1[0]);
		close(fd2[1]);

		char line[MAXLINE];
		while (fgets(line, MAXLINE, stdin) != NULL) {
			int n = strlen(line);
			if (write(fd1[1], line, n) != n)
				err_sys("write error to pipe");
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if (n == 0) {
				err_sys("child close pipe");
				break;
			}

			line[n] = 0;
			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}

		if (ferror(stdin))
			err_sys("fgets error on stdin");

		exit(0);
	} else {
		close(fd1[1]);
		close(fd2[0]);

		if (fd1[0] != STDIN_FILENO) {
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}

		if (fd2[1] != STDOUT_FILENO) {
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdout");
			close(fd2[1]);
		}

		if (execl("./add2_buf", "add2_buf", (char*)0) < 0)
			err_sys("execl error");
	}

	exit(0);
}

static void
sig_pipe(int signo) {
	printf("SIGPIPE caught\n");
	exit(1);
}
