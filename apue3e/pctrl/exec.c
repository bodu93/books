#include "../include/apue.h"

#include <sys/wait.h>
#include <unistd.h>

char* env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main() {
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		if (execle("./echoarg", "i'm not arg0, blabla", "myarg1", "myarg2", (char*)0, env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	//if ((pid = fork()) < 0) {
	//	err_sys("fork error");
	//} else if (pid == 0) {
	//	if (execlp("echoarg", "echoarg", "only 1 arg", (char*)0) < 0)
	//		err_sys("execlp error");
	//}

	exit(0);
}
