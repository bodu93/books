/* Compute prefix sum of vector a */
void psum1(float a[], float p[], long n) {
    long i;

    // original version
    // p[0] = a[0];
    // for (i = 1; i < n; i++) {
    //      p[i] = p[i - 1] + a[i];
    // }

    // re-write version: eliminate write/read dependency
    long r = 0;
    for (i = 0; i < n; i++) {
        r += a[i];
        p[i] = r;
    }
}
