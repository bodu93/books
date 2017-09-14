#include <stdio.h>

int tmult_ok(long, long, long *);

int main() {
    long result;
    tmult_ok(1, 2, &result);
    printf("%ld\n", result);

    return 0;
}
