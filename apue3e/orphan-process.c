#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

static void sig_hup(int signo) {
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(const char* name) {
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
            name, (long)getpid(), (long)getppid(), (long)getpgrp(),
            (long)tcgetpgrp(STDIN_FILENO));
    fflush(stdout);
}

int main() {
    pr_ids("parent");

    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork error\n");
        exit(1);
    } else if (pid > 0) { /* parent */
        sleep(5);
    } else {              /* child */
        pr_ids("child");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP); /* stop ourself: similar with Ctrl+Z, and let parent process exit */
        pr_ids("child");         /* child process become a orphan process, kernel send a signal SIGHUP and signal SIGCONT to every stopped process. */
        char c;
        if (read(STDIN_FILENO, &c, 1) != 1) /* EIO == 5 */
            printf("read error %d on controlling TTY\n", errno);
    }

    exit(0);
}
