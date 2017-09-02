#include <iostream>

int C;

class C {
private:
	int i[2];
public:
	static int f() {
		return sizeof(C);
	}
};

int f() {
	return sizeof(C);
}

int main() {
	C::f();
	::f();

	return 0;
}
