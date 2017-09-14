int tmult_ok2(long x, long y, long *dest) {
    int result;

    *dest = x * y;
    asm("setae      %%bl\n\t"
        "movzbl     %%bl, %[val]"
        : [val] "=r" (result)
        :
        : "%bl"
       );

    return result;
}
