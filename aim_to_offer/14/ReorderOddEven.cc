#include <stddef.h>
#include <assert.h>

#include <vector>
#include <algorithm>
#include <iostream>

bool isOdd(int n) {
	// should not n % 2 == 1
	return n % 2 != 0;
}

void ReorderOddEven(int* data, size_t length) {
	if (data == nullptr || length <= 1) return;

	assert(length >= 2);
	int* first = data;
	int* last = data + length - 1;

	while (first < last) {
		while (first < last && isOdd(*first)) ++first;
		while (first < last && !isOdd(*last)) --last;

		if (first < last)
			std::iter_swap(first++, last++);
	}
}

void ReorderOddEven_2(int* data, size_t length) {
	std::partition(data, data + length, isOdd);
}

template<typename C>
void print(const C& c) {
	std::copy(c.begin(), c.end(),
			std::ostream_iterator<typename C::value_type>{std::cout, " "});
	std::cout << std::endl;
}

void test(std::vector<int> v) {
	// ReorderOddEven(v.data(), v.size());
	ReorderOddEven_2(v.data(), v.size());
	print(v);
}

int main() {
	std::vector<int> ivec{ 2, 1 };
	test(ivec);

	ivec.assign({ 1, -1, -3, 4, -4 });
	test(ivec);

	ivec.assign({ -2, 2, -2, 2, 1, -1, 1, -1 });
	test(ivec);

	ivec.assign({ 2, -1, 1 });
	test(ivec);

	ivec.assign({ 1, 1, 1});
	test(ivec);

	ivec.assign({2, 2, 2});
	test(ivec);

	return 0;
}
