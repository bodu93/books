#include <stdlib.h>
#include <stdio.h>

/* clang malloc_test.c -DTESTTIMES=100 */
/* #define TESTTIMES 1000 */

int main() {
    for (int i = 0; i < TESTTIMES; ++i) {
        void *bufp = malloc(8);
        if (bufp) {
            printf(((size_t)bufp % 8 == 0) ? "true\n" : "false\n");
        }
    }

    return 0;
}
