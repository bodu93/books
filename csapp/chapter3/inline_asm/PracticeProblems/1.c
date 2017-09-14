int tmult_ok(long x, long y, long *dest) {
    unsigned char result;

    // Pseudo-code
    // imulq %rdi, %rsi
    // movq  %rsi, (%rdx)
    // setae %al
    // ret
    asm("imulq %%rdi, %%rsi     \n\t"
        "movq %%rsi, (%%rdx)      \n\t"
        "setae %[x]"
        : [x] "=r" (result)
       );

    return (int)result;
}
