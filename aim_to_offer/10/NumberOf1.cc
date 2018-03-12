/*
 * input an integer, output the count of bit 1 in binary format of that integer
 */

int NumberOf1(int n) {
	int countOfOne = 0;

	unsigned int bitMatch = 1;
	while (bitMatch != 0) {
		if ((bitMatch & n) != 0) ++countOfOne;
		bitMatch <<= 1;
	}

	return countOfOne;
}

int NumberOf1_2(int n) {
	int countOfOne = 0;

	while (n) {
		++countOfOne;
		n = (n - 1) & n;
	}

	return countOfOne;
}

#include <iostream>

void test(int n) {
	std::cout << NumberOf1(n) << std::endl;
}

void test_2(int n) {
	std::cout << NumberOf1_2(n) << std::endl;
}

int main() {
	test(0x7FFFFFFF); test_2(0x7FFFFFFF);
	test(0x80000000); test_2(0x80000000);
	test(0xFFFFFFFF); test_2(0xFFFFFFFF);
	test(0); test_2(0);

	return 0;
}
