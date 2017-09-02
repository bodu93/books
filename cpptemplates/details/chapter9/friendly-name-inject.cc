// 9.2.2

template <typename T>
class C {
	// ...
	// NOTE: 友元声明不是函数声明
	friend void f();
	friend void f(const C<T> &);
	// ...
};

void g(C<int> *p) {
	// f() 在此处不可见, 没有函数声明
	f();
	// f(const C<T> &)可见(ADL)
	f(*p);
}
