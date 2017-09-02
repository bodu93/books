template <typename T>
class Shell {
public:
	template <int N>
	class In {
	public:
		template <int M>
		class Deep {
		public:
			virtual void f();
		};
	};
};

template <typename T, int N>
class Weird {
public:
	void case1(typename Shell<T>::template In<N>::template Deep<N> *p) {
		// f can't be virtual function
		p->template Deep<N>::f();
	}


	void case1(typename Shell<T>::template In<N>::template Deep<N> &p) {
		// f can't be virtual function
		p.template Deep<N>::f();
	}
};


/*
 * 如果限定符号前面的名称或者表达式的类型要依赖于某个模板参数, 并且紧接在限定符后面的是一个template-id(就是指一个后面带有尖括号内部实参列表的模板名称),那么就应该使用关键字template.
