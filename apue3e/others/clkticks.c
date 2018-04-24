#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    errno = 0;
    
    long tickpersec = sysconf(_SC_CLK_TCK);
    if (tickpersec < 0) {
        if (errno == 0)
            fprintf(stderr, "indetermination of %s\n", "_SC_CLK_TCK");
        else
            fprintf(stderr, "sysconf error of %s\n", "_SC_CLK_TCK");
    } else {
        printf("ticks per sec: %ld\n", tickpersec);
    }

    exit(0);
}
