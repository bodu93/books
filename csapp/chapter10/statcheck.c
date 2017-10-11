#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

static void unixerror(const char *errmsg) {
    perror(errmsg);
    exit(1);
}

static int Stat(const char *fname, struct stat *buf) {
    int result = stat(fname, buf);
    if (result == -1) unixerror("stat failed");

    return result;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "invalid params");
        exit(1);
    }

    struct stat fstat;

    char *type;
    Stat(argv[1], &fstat);
    if (S_ISREG(fstat.st_mode))
        type = "regular";
    else if (S_ISDIR(fstat.st_mode))
        type = "directory";
    else
        type = "other";
    
    char *readok;
    if ((fstat.st_mode & S_IRUSR))
        readok = "yes";
    else
        readok = "no";

    printf("type: %s read: %s\n", type, readok);

    exit(0);
}
