#include <string>

template <typename T>
inline T max(T a, T b) {
	return a < b ? b : a;
}

int main() {
	std::string s;

	::max("apple", "peach");
	::max("apple", "tomato");
	::max("apple", s);

	return 0;
}
