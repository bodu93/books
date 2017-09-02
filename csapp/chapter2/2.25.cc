#include <iostream>

float sum_elements(float a[], unsigned length) {
	int i;
	float result = 0;

	for (i = 0; i != length; i++) {
		result += a[i];
	}
	
	return result;
}

int main() {
	float a[] = { 1.1 };
	std::cout << sum_elements(a, 0) << std::endl;

	return 0;
}
