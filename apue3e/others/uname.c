#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct utsname nameinfo;
    if (uname(&nameinfo) < 0) {
        perror("uname");
        exit(1);
    }

    printf("%s\n", nameinfo.sysname);
    printf("%s\n", nameinfo.nodename);
    printf("%s\n", nameinfo.release);
    printf("%s\n", nameinfo.version);
    printf("%s\n", nameinfo.machine);

    return 0;
}
