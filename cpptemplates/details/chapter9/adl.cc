// 9.2.1: ADL(Argument-Dependent Lookup)

#include <iostream>

namespace X {
	template <typename T> void f(T);
}

namespace N {
	// ADL将忽略using指示
	using namespace X;
	enum E { e1 };
	void f(E) {
		std::cout << "N::f(N::E) called" << std::endl;
	}
}

void f(int) {
	std::cout << "::f(int) called" << std::endl;
}

int main() {
	::f(N::e1);
	f(N::e1);

	return 0;
}
