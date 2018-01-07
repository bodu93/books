#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    errno = 0;
    int err = sysconf(_PC_CHOWN_RESTRICTED);
    if (err < 0) {
        if (errno == 0)
            fprintf(stderr, "indetermination of %s\n", "_PC_CHOWN_RESTRICTED");
        else
            fprintf(stderr, "sysconf error for %s\n", "_PC_CHOWN_RESTRICTED");
    } else {
        printf("%d\n", err);
    }

    exit(0);
}
