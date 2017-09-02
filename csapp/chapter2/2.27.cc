#include <limits>
#include <stdint.h>
#include <iostream>

int uadd_ok(unsigned x, unsigned y) {
	unsigned r = x + y;
	return !(r < x || r < y);
}

int main() {
	int r = uadd_ok(std::numeric_limits<unsigned>::max(),
			std::numeric_limits<unsigned>::max());

	std::cout << r << std::endl;

	return 0;
}
