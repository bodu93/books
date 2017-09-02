#include <limits>
#include <stdint.h>
#include <iostream>

int tadd_ok(int x, int y) {
	int r = x + y;
	if ((x < 0 && y < 0 && r >= 0) ||
		(x > 0 && y > 0 && r <= 0))
		return 0;
	return 1;
}

int main() {
	int r = tadd_ok(std::numeric_limits<int>::min(),
			std::numeric_limits<int>::min());
	std::cout << r << std::endl;
	return 0;
}
