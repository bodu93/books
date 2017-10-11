#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void unix_error(const char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void *Mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset) {
    void *address =
        mmap(start, length, prot, flags, fd, offset);
    if (address == MAP_FAILED) {
        /* mmap on STDOUT_FILENO : mmap not supported on device */
        unix_error("mmap failed");
    }
    return address;
}

int Munmap(void *start, size_t length) {
    int result = munmap(start, length);
    if (result == -1) {
        unix_error("mummap failed");
    }

    return result;
}

int Open(const char *pathname, int flags) {
    int fd = open(pathname, flags);
    if (fd < 0) {
        unix_error("open error");
    }
    return fd;
}

int Close(int fd) {
    int result = close(fd);
    if (result < 0) {
        unix_error("close error");
    }

    return result;
}

ssize_t Write(int fd, const void *buf, size_t n) {
    ssize_t wn = write(fd, buf, n);
    if (wn < 0) {
        unix_error("write error");
    }
    return wn;
}

void MmapCopy(int fd, size_t length) {
    void *bufp = Mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    Write(STDOUT_FILENO, bufp, length);
    Munmap(bufp, length);
}

void Memcopy(void *dest, const void *src, size_t length) {
    memcpy(dest, src, length);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    int infd = Open(argv[1], O_RDONLY);
    struct stat fstate;
    fstat(infd, &fstate);
    MmapCopy(infd, fstate.st_size);
    Close(infd);

    //int infd = Open(argv[1], O_RDONLY);
    //int outfd = STDOUT_FILENO;

    //struct stat fs;
    //fstat(infd, &fs);
    //void *src = Mmap(0, fs.st_size, PROT_READ, MAP_PRIVATE, infd, 0);
    //void *dest = Mmap(0, fs.st_size, PROT_WRITE, MAP_SHARED, outfd, 0);
    //Memcopy(dest, src, fs.st_size);

    //Munmap(src, fs.st_size);
    //Munmap(dest, fs.st_size);

    return 0;
}
