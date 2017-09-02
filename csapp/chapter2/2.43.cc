#include <iostream>
#include <limits>

#define M 31
#define N 8

int arith(int x, int y) {
	int result = 0;
	result = x * M + y / N;
	return result;
}

int optarith(int x, int y) {
	int t = x;
	x <<= 5;
	x -= t;
	if (y < 0) y += 7;
	y >>= 3;
	return x + y;
}

int main() {
	int x = std::numeric_limits<int>::max();
	int y = std::numeric_limits<int>::min();
	std::cout << (arith(x, y) == optarith(x, y)) << std::endl;

	return 0;
}
