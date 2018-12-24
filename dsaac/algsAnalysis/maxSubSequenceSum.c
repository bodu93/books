/*
 * maxSubSequenceSum.c
 */
#include <sys/time.h> // for struct timeval and gettimeofday
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int v1_maxSubSequenceSum(const int A[], int N) {
  int maxSum = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i; j < N; ++j) {
      int sum = 0;
      for (int k = i; k <= j; ++k) {
        sum += A[k];
      }
      if (sum > maxSum) {
        maxSum = sum;
      }
    }
  }
  return maxSum;
}

void v1_unittestMaxSubSequenceSum() {
  int a[] = { -9, 1, 2, -4, 3, 0, -42 };
  assert(3 == v1_maxSubSequenceSum(a, 7));
  int a1[] = { 1 };
  assert(1 == v1_maxSubSequenceSum(a1, 1));
  int a2[] = { 1, -11 };
  assert(1 == v1_maxSubSequenceSum(a2, 2));
  int a3[] = { -42 };
  assert(0 == v1_maxSubSequenceSum(a3, 1));
}

int v2_maxSubSequenceSum(const int A[], int N) {
  int maxSum = 0;
  for (int i = 0; i < N; ++i) {
    int sum = 0;
    for (int j = i; j < N; ++j) {
      sum += A[j];
      if (sum > maxSum) {
        maxSum = sum;
      }
    }
  }
  return maxSum;
}

void v2_unittestMaxSubSequenceSum() {
  int a[] = { 1, 2, 3, 4, 5 };
  assert(15 == v2_maxSubSequenceSum(a, 5));
  int a1[] = { 1, -12, 1 };
  assert(1 == v2_maxSubSequenceSum(a1, 3));
  int a2[] = { 1 };
  assert(1 == v2_maxSubSequenceSum(a2, 1));
  int a3[] = { -42 };
  assert(0 == v2_maxSubSequenceSum(a3, 1));
}

static int max(int l, int r) {
  return l > r ? l : r;
}

static int max3(int l, int c, int r) {
  int lc = max(l, c);
  return max(lc, r);
}

// A[left, right]
static int maxSubSum(const int A[], int left, int right) {
  if (left == right) { // base case
    if (A[left] > 0) {
      return A[left];
    } else {
      return 0;
    }
  }

  int center = (left + right) / 2;
  int maxLeftSum = maxSubSum(A, left, center);
  int maxRightSum = maxSubSum(A, center + 1, right);

  int maxLeftBorderSum = 0;
  for (int i = center; i >= left; --i) {
    maxLeftBorderSum += A[i];
  }

  int maxRightBorderSum = 0;
  for (int i = center + 1; i <= right; ++i) {
    maxRightBorderSum += A[i];
  }

  return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int v3_maxSubSequenceSum(const int A[], int N) {
  assert(N > 0);
  return maxSubSum(A, 0, N - 1);
}

void v3_unittestMaxSubSequenceSum() {
  int a[] = { -42 };
  assert(0 == v3_maxSubSequenceSum(a, 1));
  int a1[] = { 1, 2, 3, 4, 5 };
  assert(15 == v3_maxSubSequenceSum(a1, 5));
  int a2[] = { -1, 42, -1, -1, -41 };
  assert(42 == v3_maxSubSequenceSum(a2, 5));
}

int v4_maxSubSequenceSum(const int A[], int N) {
  int maxSum = 0;
  int sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += A[i];
    if (sum > maxSum) {
      maxSum = sum;
    } else if (sum < 0) {
      sum = 0;
    }
  }
  return maxSum;
}

void v4_unittestMaxSubSequenceSum() {
  int a[] = { -42 };
  assert(0 == v4_maxSubSequenceSum(a, 1));
  int a1[] = { 1, 2, 3, 4, 5 };
  assert(15 == v4_maxSubSequenceSum(a1, 5));
  int a2[] = { -42, 1, 32 };
  assert(33 == v4_maxSubSequenceSum(a2, 3));
}

int main() {
  // v1_unittestMaxSubSequenceSum();
  // v2_unittestMaxSubSequenceSum();
  // v3_unittestMaxSubSequenceSum();
  v4_unittestMaxSubSequenceSum();

  return 0;
}
