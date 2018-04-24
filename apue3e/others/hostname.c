#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    char hostnamebuf[BUFSIZ];
    if (gethostname(hostnamebuf, BUFSIZ) < 0) {
        perror("gethostname");
        exit(1);
    }
    hostnamebuf[BUFSIZ - 1] = '\0';
    
    printf("%s\n", hostnamebuf);

    return 0;
}
