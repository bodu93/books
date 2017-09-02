#include <stdint.h>
#include <limits>
#include <iostream>

int tmult_ok(int32_t x, int32_t y) {
	int64_t r = x * y;
	return r == static_cast<int32_t>(r);
}

int main() {
	int r = tmult_ok(std::numeric_limits<int32_t>::max(),
			std::numeric_limits<int32_t>::max());
	std::cout << r << std::endl;

	return 0;
}
