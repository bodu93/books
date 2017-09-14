int tmult_ok3(long x, long y, long *dest) {
    unsigned char bresult;
    *dest = x * y;

    asm("setae  %[b]"
        : [b] "=r" (bresult)
       );

    return (int)bresult;
}
