int main() {
    unsigned long invalid_addr = (1ul << 48);
    int *invalid_ptr = invalid_addr;

    *invalid_ptr = 111;
    return 0;
}
