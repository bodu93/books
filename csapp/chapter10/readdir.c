#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdlib.h>
#include <stdio.h>

void unixerror(const char *errmsg) {
    perror(errmsg);
    exit(1);
}

DIR *Opendir(const char *name) {
    DIR *result = opendir(name);
    if (!result) unixerror("open dir failed");

    return result;
}

int main(int argc, char **argv) {
