#include <queue>
#include <assert.h>

#include <iostream>

template<typename T>
class Stack {
private:
	std::queue<T> q1;
	std::queue<T> q2;

public:
	Stack() = default;

	void push(const T& v) {
		bool q1empty = q1.empty();
		bool q2empty = q2.empty();

		if (q1empty && q2empty) q1.push(v);
		else if (q1empty) q2.push(v);
		else q1.push(v);
	}

	T pop() {
		if (empty()) return T();
		// else throw a exception

		bool q1empty = q1.empty();
		T t;
		if (q1empty) {
			while (q2.size() != 1) {
				q1.push(q2.front());
				q2.pop();
			}

			t = q2.front();
			q2.pop();
		} else {
			while (q1.size() != 1) {
				q2.push(q1.front());
				q1.pop();
			}

			t = q1.front();
			q1.pop();
		}

		return t;
	}

	bool empty() const {
		return q1.empty() && q2.empty();
	}
};

int main() {
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	std::cout << s.pop() << std::endl;
	std::cout << s.pop() << std::endl;

	s.push(4);
	s.push(5);

	std::cout << s.pop() << std::endl;

	while (!s.empty()) {
		s.pop();
	}

	s.push(6);
	std::cout << s.pop() << std::endl;

	assert(s.empty());

	return 0;
}
