#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define oops(m,x) { perror(m); exit(x); }

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s file file timeout\n", *argv);
        exit(1);
    }

    /* ope files */
    int fd1;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
        oops(argv[1], 2);
    
    int fd2;
    if ((fd2 = open(argv[2], O_RDONLY)) == -1)
        oops(argv[2], 3);

    int maxfd = 1 + (fd1 > fd2 ? fd1 : fd2);

    fd_set readfds;
    struct timeval timeout;
    void showdata(char* fname, int fd);
    while (1) {
        /* make a list of file descriptors to watch */
        FD_ZERO(&readfds);
        FD_SET(fd1, &readfds);
        FD_SET(fd2, &readfds);

        /* set timeout value */
        timeout.tv_sec = atoi(argv[3]);
        timeout.tv_usec = 0;

        /* wait for input */
        int retval = select(maxfd, &readfds, NULL, NULL, &timeout);
        if (retval < 0) {
            oops("select", 4);
        }

        if (retval > 0) {
            /* check bits for each fd */
            if (FD_ISSET(fd1, &readfds))
                showdata(argv[1], fd1);
            if (FD_ISSET(fd2, &readfds))
                showdata(argv[2], fd2);
        } else {
            printf("no input after %d seconds\n", atoi(argv[3]));
        }
    }

    exit(0);
}

void showdata(char* fname, int fd) {
    printf("%s:\n", fname);
    fflush(stdout);

    char buf[BUFSIZ];
    ssize_t n = read(fd, buf, BUFSIZ);
    if (n < 0)
        oops(fname, 5);

    write(STDOUT_FILENO, buf, n);
    write(STDOUT_FILENO, "\n", 1);
}
