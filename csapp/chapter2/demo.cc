#include <limits>
#include <iostream>

int main() {
	double d = 1e10;
	int v = static_cast<int>(d);
	std::cout << (v == std::numeric_limits<int>::min()) << std::endl;

	return 0;
}
