/*
 * selection problem: find kth number from N elements(k = N/2)
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

static void swapInts(int* lhs, int* rhs) {
  int mid = *lhs;
  *lhs = *rhs;
  *rhs = mid;
}

static unsigned long currentMicroSeconds() {
  struct timeval curval;
  gettimeofday(&curval, NULL);
  return curval.tv_sec * 1000 * 1000 + curval.tv_usec;
}

void bubbleSort(int* array, int N) {
  if (N == 1) return;

  for (int i = N - 1; i > 0; --i) {
    bool ordered = true;
    for (int j = 0; j < i; ++j) {
      if (array[j] < array[j + 1]) {
        swapInts(array + j, array + j + 1);
        ordered = false;
      }
    }
    if (ordered) break;
  }
}

void testBubbleSort(int* array, int N) {
  bubbleSort(array, N);
  for (int i = 0; i < N; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void unittestBubbleSort() {
  int a1[] = { 1, 2, 3, 4 };
  testBubbleSort(a1, 4);
  int a2[] = { 4, 3, 2, 1 };
  testBubbleSort(a2, 4);
  int a3[] = { 1 };
  testBubbleSort(a3, 1);
  int a4[] = { 3, 4, 1, 2, 5 };
  testBubbleSort(a4, 5);
}

int findKth(int* array, int N, int K) {
  assert(K >= 1);
  assert(N >= K);
  int karray[K];
  memcpy(karray, array, sizeof(int) * K);
  bubbleSort(karray, K);
  for (int i = K; i < N; ++i) {
    int a = array[i];
    for (int j = K - 1; j >= 0; --j) {
      if (karray[j] > a) {
        for (int k = K - 1; k > j + 1; --k) {
          karray[k] = karray[k - 1];
        }
        karray[j + 1] = a;
      }
    }
  }
  return array[K - 1];
}

void testFindKth(int* array, int N, int K) {
  int kth = findKth(array, N, K);
  printf("N = %d, K = %d, kth = %d\n", N, K, kth);
}

void unittestFindKth() {
  int a1[] = { 1, 2, 3, 4 };
  testFindKth(a1, 4, 2); // 2
  testFindKth(a1, 4, 4); // 4
  testFindKth(a1, 4, 1); // 1
  int a2[] = { 1 };
  testFindKth(a2, 1, 1); // 1
  int a3[] = { 5, 1, 2, 4, 3 };
  testFindKth(a3, 5, 4); // 4
}

void timeFindKth(int N) {
  int array[N];
  for (int i = 0; i < N; ++i) {
    array[i] = rand() % N;
  }

  unsigned long startMicroSeconds = currentMicroSeconds();
  findKth(array, N, N / 2);
  unsigned long endMicroSeconds = currentMicroSeconds();

  printf("N = %d, K = %d, time: %lu microseconds\n",
      N, N / 2, endMicroSeconds - startMicroSeconds);
}

int main() {
  // unittestBubbleSort();
  // unittestFindKth();
  timeFindKth(100);
  timeFindKth(1000);
  timeFindKth(10000);
  timeFindKth(100000);
  timeFindKth(1000000);

  return 0;
}
