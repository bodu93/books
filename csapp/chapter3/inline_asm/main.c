#include <stdio.h>

int main() {
    long c = 0;
    tmult_ok_asm(1, 2, &c);

    printf("%ld\n", c);

    return 0;
}
