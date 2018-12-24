/*
 * mainElement.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int findMainElement(const int A[], int N) {
  if (0 == N) return -1; // no main element in this array A[]
  if (1 == N) return A[0];

  // int B[N / 2 + 1];
  // don't use array B:)
  int* B = (int*)A;
  int idx = 0;
  for (int i = 0; i < N; i += 2) {
    if ((i + 1 < N && A[i] == A[i + 1]) ||
        i + 1 == N) {
      B[idx++] = A[i];
    }
  }
  return findMainElement(B, idx);
}

void unittestFindMainElement() {
  int a[] = { 1 };
  assert(1 == findMainElement(a, 1));
  int a1[] = { 1, 2, 1, 2, 1, 2 };
  assert(-1 == findMainElement(a1, 6));
  int a2[] = { 1, 3, 1, 3, 3 };
  assert(3 == findMainElement(a2, 5));
}

int main() {
  unittestFindMainElement(); // yes, this algorithm is correct, but why??

  return 0;
}
