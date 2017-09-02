template <typename T>
class BXT {
public:
	typedef T Mystery;

	template <typename U>
	struct Magic;
};

template <typename T>
class DXTT : private BXT<T> {
public:
	// can't compile??
	using typename BXT<T>::Mystery;
	Mystery * p;
};

template <typename T>
class DXTM : private BXT<T> {
public:
	// can't compile??
	using BXT<T>::template Magic;
	Magic<T> *plink;
};
