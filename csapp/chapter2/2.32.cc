#include <limits>
#include <iostream>

int main() {
	int v = std::numeric_limits<int>::min();
	int r = v - 1;
	std::cout << (r == std::numeric_limits<int>::max()) << std::endl;

	return 0;
}
