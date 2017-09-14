#include <iostream>

template <typename T>
int fact_max_number() {
	T result = 1;
	int loop = 1;
	while (result > 0) {
		result *= loop++;
	}

	return loop - 1;
}

int main() {
	std::cout << fact_max_number<int>() << std::endl;
	std::cout << fact_max_number<long>() << std::endl;

	return 0;
}
