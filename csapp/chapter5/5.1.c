#include <stdio.h>

void swap(long *xp, long *yp) {
    *xp = *xp + *yp;
    *yp = *xp - *yp;
    *xp = *xp - *yp;
}

int main() {
    long x = 1;
    long y = 2;

    swap(&x, &y);
    printf("%ld  %ld\n", x, y);
    
    swap(&x, &x);
    printf("%ld\n", x);

    return 0; 
}
