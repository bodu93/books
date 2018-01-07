#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    extern char** environ;
    
    for (int i = 0; i < argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);

    char** ptr;
    for (ptr = environ; *ptr != 0; ++ptr)
        printf("%s\n", *ptr);

    exit(0);
}
