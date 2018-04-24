#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

char buf[500000];

void set_fl(int fd, int flags) {
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fputs("fcntl F_GETFL error\n", stderr);
        exit(1);
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        fputs("fcntl F_SETFL error\n", stderr);
        exit(1);
    }
}

void clr_fl(int fd, int flags) {
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        fputs("fcntl F_GETFL error\n", stderr);
        exit(1);
    }

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        fputs("fcntl F_SETFL error\n", stderr);
        exit(1);
    }
}

int main() {
    int ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    set_fl(STDOUT_FILENO, O_NONBLOCK); /* set stdout nonblocking */

    char* ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        int nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }

    clr_fl(STDOUT_FILENO, O_NONBLOCK);

    exit(1);
}
