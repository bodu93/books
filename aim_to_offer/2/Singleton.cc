/*
 * 设计一个类，我们只能生成该类的一个实例
 */

template<typename T>
class Singleton {
private:
	Singleton();

	static void init() {
		value_ = new T();
	}

	static void destroy() {
		delete value_;
	}

	static T*				value_;
public:
	/*
	 * full locking(in C++03) around the
	 * instantiating method is basically
	 * the simplest way to ensure proper
	 * concurrency on all platforms.
	 * https://stackoverflow.com/questions/1661529/is-meyers-implementation-of-the-singleton-pattern-thread-safe
	 */
	T& instance() {
		MutexGuard<Mutex> guard(&lock);
		if (value_ == NULL) init();
		return *value_;
	}

	/*
	 * (post)C++11 solution
	 * T& instance() {
	 * static T s;
	 * return s;
	 * }
	 */

	~Singleton() {
		delete value_;
	}
};

template<typename T> T* Singleton<T>::value_ = NULL;
