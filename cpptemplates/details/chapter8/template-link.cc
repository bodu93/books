int C;

class C;

// 8.1.2: 类模板不能喝另外一个实体共享一个名称, 这一点和class类型是不同的.
int X;
template <typename T>
class X;

struct S;

template <typename T>
class S;
