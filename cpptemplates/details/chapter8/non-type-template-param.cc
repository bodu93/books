template <typename T, T nontype_param>
class C;

class Base {
public:
	int i;
} base;

class Derived : public Base { } derived_obj;

C<Base *, &derived_obj> *err1;
C<int&, base.i> *err2;

int a[10];
C<int*, &a[0]> *err3;


/*
 * 非类型模板实参就是替换非类型模板参数的值, 这个值必须是以下几种中的一种:
 * . 某一个具有正确类型的非类型模板参数
 * . 一个编译期整型常量。这只有在参数类型和值的类型能够进行匹配, 或者值的类型可以隐式地转换为参数类型的前提下才是合法的
 * . 前面有单目运算符&(即取址)的外部变量或者函数的名称. 对于函数或数组变量, &运算符可以省略。这类模板实参可以匹配指针类型的非类型参数
 * . 对于引用类型的非类型模板参数，前面没有&运算符的外部变量和外部函数也是可取的.
 * . 一个指向成员的指针常量, 换句话说, 类似&C::m的表达式, 其中C是一个class类型, m是一个非静态成员(成员变量或函数).这类实参只能匹配类型为"成员指针"的非类型实参
 *
 * NOTES: 当实参匹配"指针类型或引用类型的参数"时, 用户自定义类型转换(隐式的单参数构造函数和重载类型转换运算符)和由派生类到基类的类型转换都是不会被考虑的.
 */
