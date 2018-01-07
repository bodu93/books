#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        if (execle("./echo_env", "echo_env", "myarg1", "MY ARG2", (char*)0, env_init) < 0) {
            fprintf(stderr, "execle error\n");
            exit(1);
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        fprintf(stderr, "wait error\n");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid == 0) {
        if (execlp("./echo_env", "echo_env", "only 1 arg", (char*)0) < 0) {
            fprintf(stderr, "execlp error\n");
            exit(1);
        }
    }

    exit(0);
}
