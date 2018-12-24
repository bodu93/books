/*
 * printDigit.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void printUnsignedDigit(unsigned n) {
  if (n > 0) {
    printUnsignedDigit(n / 10);
    printf("%d", n % 10);
  }
}

void printDigit(int n) {
  if (n < 0) {
    printf("-");
    printUnsignedDigit(-n);
  } else {
    printUnsignedDigit(n);
  }
  printf("\n");
}

int main() {
  printDigit(INT_MIN);
  printDigit(INT_MAX);
  printDigit(0);

  return 0;
}
