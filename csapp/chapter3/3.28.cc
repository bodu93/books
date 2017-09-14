#include <limits>
#include <iostream>

long fun_b(unsigned long x) {
	long val = 0;
	long i;
	for (i = 64; i != 0; --i) {
		val <<= 1;
		val |= (x & 1);
		x >>= 1;
	}

	return val;
}

int main() {
	unsigned long x = 1;
	long result = std::numeric_limits<long>::min();
	std::cout << (fun_b(x) == result) << std::endl;

	x = -2;
	result = std::numeric_limits<long>::max();
	std::cout << (fun_b(x) == result) << std::endl;

	return 0;
}
