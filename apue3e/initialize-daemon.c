#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

void initializeDaemon(const char* cmd) {
    /*
     * clear file creation mask
     */
    umask(0);

    /*
     * get maximum number of file descriptors.
     */ 
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        fprintf(stderr, "%s: can't get file limit\n", cmd);
        exit(1);
    }

    /*
     * become a session leader to lose controlling TTY.
     */
    pid_t pid;
    if ((pid = fork()) < 0) {
        fprintf(stderr, "%s: can't fork\n", cmd);
        exit(1);
    } else if (pid != 0) {
        exit(0);
    }
    /* first fork: child process begin... */
    setsid();

    /*
     * ensure future opens won't allocate controlling TTY.
     */
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;    /* ignore SIGHUP */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        fprintf(stderr, "%s: can't ignore SIGHUP\n", cmd);
        exit(1);
    }
    if ((pid = fork()) < 0) {
        fprintf(stderr, "%s: can't fork\n", cmd);
        exit(1);
    }
    else if (pid != 0) {
        exit(0);
    }
    /* second fork: child process begin... */

    /*
     * change the current working directory to the root so
     * we don't prevent file systems from being unmounted
     */
    if (chdir("/") < 0) {
        fprintf(stderr, "%s: can't change directory to /\n", cmd);
        exit(1);
    }

    /*
     * close all open file descriptors.
     */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (int i = 0; i < rl.rlim_max; i++)
        close(i);

    /*
     * Attach file descriptors 0, 1, and 2 to /dev/null
     */
    int fd0 = open("/dev/null", O_RDWR);    /* fd0 == 0 */
    int fd1 = dup(0);                       /* fd1 == 1 */
    int fd2 = dup(0);                       /* fd2 == 2 */

    /*
     * initialize the log file
     */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}
