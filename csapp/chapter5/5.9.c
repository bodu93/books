void merge(long src1[], long src2[], long dest[], long n) {
    long i1 = 0;
    long i2 = 0;
    long id = 0;
    while (i1 < n && i2 < n) {
        bool wise = src1[i1] < src2[i2];
        long min = wise ? src1[i1] : src2[i2];
        long *minrank = wise ? &i1 : &i2;
        ++(*minrank);
        dest[id++] = min;
    }

    while (i1 < n)
        dest[id++] = src1[i1++];
    while (i2 < n)
        dest[id++] = src2[i2++];
}
