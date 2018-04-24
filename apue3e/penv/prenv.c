#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int main() {
	for (char** envp = environ; (*envp) != NULL; ++envp)
		printf("%s\n", *envp);

	exit(0);
}
