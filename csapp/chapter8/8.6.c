#include "csapp.h"

int main(int argc, char **argv, char **envp) {
    printf("Command-line arguments:\n");
    for (int i = 0; i != argc; ++i) {
        printf("argv[%2d]: %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");
    int rank = 0;
    while (*envp) {
        printf("envp[%2d]: %s\n", rank, *envp);
        ++rank;
        ++envp;
    }

    return 0;
}
