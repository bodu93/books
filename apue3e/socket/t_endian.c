#include <stdio.h>
#include <stdint.h>

int main() {
	int32_t v = 0x04030201;

	char* cp = (char*)&v;
	printf(*cp == 1 ? "little endian\n" : "big endian\n");

	return 0;
}
