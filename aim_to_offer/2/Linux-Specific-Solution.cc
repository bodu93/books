/*
 * linux-specific singleton solution
 * from chenshuo's Muduo Library
 */
#include <pthread.h>
#include <stdlib.h> // atexit

template<typename T>
class Singleton {
private:
	Singleton();
	~Singleton();

	static void init() {
		value_ = new T();
		// register a destroy callback
		// called when process exit
		::atexit(destroy);
	}

	static void destroy() {
		delete value_;
	}

	static T*									value_;
	static pthread_once_t 		once_;
public:
	static T& instance() {
		pthread_once(&once_, &Singleton::init);
		return *value_;
	}
};

template<typename T> T* Singleton<T>::value_ = NULL;
template<typename T> pthread_once_t Singleton<T>::once_ = PTHREAD_ONCE_INIT;
