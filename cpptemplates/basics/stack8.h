#ifndef STACK_H
#define STACK_H

#include <deque>
#include <stdexcept>
#include <memory>

template <typename T,
		 template <typename ELEM,
		 			typename = std::allocator<ELEM>>
					class CONT = std::deque>
class Stack {
private:
	CONT<T> elems;

public:
	void push(T const &);
	void pop();
	T top() const;
	bool empty() const {
		return elems.empty();
	}

	template <typename T2,
			 template <
				 typename ELEM2,
			 	 typename = std::allocator<ELEM2>
					  >class CONT2>
	Stack<T, CONT> &operator=(Stack<T2, CONT2> const &);
};


#endif // STACK_H
