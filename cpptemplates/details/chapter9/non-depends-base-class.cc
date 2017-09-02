// 9.4.1实在是奇怪, 坑!!!

template <typename X>
class Base {
public:
	int basefield;
	typename int T;
};

//class D1 : public Base<Base<void>> {
//public:
//	void f() { basefield = 3; }
//};

template <typename T>
class D2 : public Base<double> {
public:
	void f() { basefield = 7; }
	// 类型T优先选择基类中的类型T, 即int类型, 而非D2的模板参数类型T
	T strange;
};

void g(D2<int*> &d2, int *p) {
	// compile error, d2.strange's type is int.
	d2.strange = p;
}
