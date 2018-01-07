/*
 * stof -- string to float
 */
#include <stdlib.h>
#include <stdio.h>

int stof(const char* str, float* out) {
    /* wrong input: null or empty str and null out */
    if (str == NULL || *str == '\0' || out == NULL) return -1;

    /* state variables */
    int dotscount = 0;
    float base = 1.0f;

    float result = 0.0f;

    const char* ptr = str;
    while (*ptr != '\0') {
        int ch = 0;
        if (*ptr == '.') {
            ++dotscount;
            if (dotscount == 2) {           /* wrong case 1 */
                *out = result;
                return -1;
            }
        } else {
            ch = *ptr - '0';

            if (ch < 0 || ch > 9) {         /* wrong case 2 */
                *out = result;
                return -1;
            }
            
            if (dotscount == 0) {
                result *= 10;
                result += ch;
            } else {
                base *= 0.1;
                result += ch * base;
            }
        }

        ++ptr;
    }
    
    *out = result;
    return 0;
}


int main() {
    /* test simple cases */
    float out = 0;
    int result = -1;

    result = stof("11.", &out);
    printf("%d %f\n", result, out);

    result = stof("12.21", &out);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    result = stof(NULL, NULL);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str1[1];
    str1[0] = '\0';
    result = stof(str1, NULL);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str2[] = ".12";
    result = stof(str2, NULL);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    result = stof(str2, &out);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str3[] = "12.";
    result = stof(str3, &out);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str4[] = "..";
    result = stof(str4, &out);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str5[] = "11..";
    result = stof(str5, &out);
    printf("%d %f\n", result, out);

    out = 0;
    result = -1;
    char str6[] = "1.1.";
    result = stof(str6, &out);
    printf("%d %f\n", result, out);

    /* other edge cases */
    /* TODO */

    return 0;
}
