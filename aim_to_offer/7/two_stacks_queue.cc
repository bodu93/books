/*
 * implement a queue using two stacks
 */
#include <stack>

#include <iostream>

template<typename T>
class Queue {
private:
	std::stack<T> stack1;
	std::stack<T> stack2;

public:
	Queue() = default;

	void appendTail(const T& v) {
		stack1.push(v);
	}

	T deleteHead() {
		if (stack2.empty()) {
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}

		T t;
		if (!stack2.empty()) {
			t = stack2.top();
			stack2.pop();
		}
		// else throw a NullQueue exception?
		return t;
	}

	bool empty() const {
		return stack1.empty() && stack2.empty();
	}
};

int main() {
	Queue<int> iq;

	iq.appendTail(1);
	iq.appendTail(2);
	std::cout << iq.deleteHead() << std::endl;
	std::cout << iq.deleteHead() << std::endl;

	iq.appendTail(3);
	iq.appendTail(4);

	std::cout << iq.deleteHead() << std::endl;

	iq.appendTail(5);
	iq.appendTail(6);

	iq.deleteHead();

	while (!iq.empty()) {
		int v = iq.deleteHead();
		std::cout << v << std::endl;
	}

	return 0;
}
