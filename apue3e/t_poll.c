#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

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

    void showdata(char* fname, int fd);
    struct pollfd readfds[2];
    readfds[0].fd = fd1;
    readfds[0].events = POLLIN;
    readfds[0].revents = 0;
    readfds[1].fd = fd2;
    readfds[1].events = POLLIN;
    readfds[1].revents = 0;
    while (1) {
        int retval = poll(readfds, sizeof(readfds), atoi(argv[3]));
        if (retval < 0) {
            oops("poll", 4);
        } else if (retval > 0) {
            if (readfds[0].revents & POLLIN)
                showdata(argv[1], fd1);
            if (readfds[1].revents & POLLIN)
                showdata(argv[2], fd2);
        } else {
            fprintf(stderr, "no input after %d seconds\n",
                    atoi(argv[3]));
        }

        readfds[0].revents = 0;
        readfds[1].revents = 0;
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
