#include <stdio.h>
#include <unistd.h>

int main() {
	printf("%ld\n", sysconf(_POSIX_V7_ILP32_OFF32));
	printf("%ld\n", sysconf(_POSIX_V7_ILP32_OFFBIG));
	printf("%ld\n", sysconf(_POSIX_V7_LP64_OFF64));
	// printf("%ld\n", sysconf(_POSIX_V7_LP64_OFFBIG));

	return 0;
}
