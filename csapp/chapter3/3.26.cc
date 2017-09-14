#include <limits>
#include <iostream>

long fun_a(unsigned long x) {
	long val = 0;
	while (x != 0) {
		val ^= x;
		x >>=1;
	}

	return val & 1;
}

int main() {
	std::cout << 
		fun_a(std::numeric_limits<unsigned long>::min()) << std::endl;

	std::cout <<
		fun_a(std::numeric_limits<unsigned long>::max()) << std::endl;

	std::cout << fun_a(1) << std::endl;

	return 0;
}
