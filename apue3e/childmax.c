#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    errno = 0;
    
    long chldmax = sysconf(_SC_CHILD_MAX);
    if (chldmax < 0) {
        if (errno == 0)
            fputs("indetermination of child max\n", stderr);
        else
            fputs("sysconf error of _SC_CHILD_MAX\n", stderr);
    } else {
        printf("child max: %ld\n", chldmax);
    }

    exit(0);
}
