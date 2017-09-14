int umult_ok(unsigned long x, unsigned long y, unsigned long *dest) {
    unsigned char bresult;

    asm("movq %[x], %%rax   # Get x\n\t"
        "mulq %[y]          # Unsigned long multiply by y\n\t"
        "movq %%rax, %[p]   # Store low-order 8 bytes at dest\n\t"
        "setae %[b]         # Set result"
        : [p] "=m" (*dest), [b] "=r" (bresult) /* outputs */
        : [x] "r" (x), [y] "r" (y)             /* inputs */
        : "%rax", "%rdx"
       );

    return (int)bresult;
}
