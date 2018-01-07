#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/* lock whole file */
extern int lockfile(int);

int already_running() {
    int fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
    if (fd < 0) {
        syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    if (lockfile(fd) < 0) {
        /* already locked: so there only one daemon running on machine?? */
        if (errno == EAGAIN || errno == EACCES) {
            close(fd);
            return 1;
        }
        syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    /* truncate file to zero */
    ftruncate(fd, 0);
    char buf[16];
    /* write pid to this file */
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
    return 0;
}
