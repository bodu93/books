#include <iostream>
#include <limits>

int div16(int x) {
	int v = (x >> 31) & 1;
	return (x + (v << 4) - v) >> 4;
}

int main() {
	int v = std::numeric_limits<int>::min();
	std::cout << (div16(v) == v / 16) << std::endl;

	v = std::numeric_limits<int>::max();
	std::cout << (div16(v) == v / 16) << std::endl;

	v = 32;
	std::cout << div16(v) << std::endl;

	v = -32;
	std::cout << div16(v) << std::endl;

	v = -1;
	std::cout << div16(v) << std::endl;

	v = -17;
	std::cout << div16(v) << std::endl;

	v = 31;
	std::cout << div16(v) << std::endl;


	return 0;
}
