/* Multiply arguments and indicate whether it did not overflow */
int umult_ok_asm(unsigned long x, unsigned long y, unsigned long *dest) {
    unsigned long p = x * y;
    *dest = p;
    return p > 0;
}
