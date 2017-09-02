#include <string.h>
#include <iostream>

int strlonger(char *s, char *t) {
	// buggy code: strlen(s) - strlen(t) > 0, always bigger than 0
	return strlen(s) > strlen(t);
}

int main() {
	std::cout << strlonger("1", "123") << std::endl;

	return 0;
}
