#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void printids(const char* thd_name) {
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n",
			thd_name, (unsigned long)pid,
			(unsigned long)tid, (unsigned long)tid);
}

void* thd_func(void* thd_arg) {
	printids("new thread: ");
	return ((void*)0);
}

int main() {
	pthread_t tid;
	int err = pthread_create(&tid, NULL, thd_func, NULL);
	if (err < 0) {
		fprintf(stderr, "can't create thread\n");
		exit(1);
	}

	printids("main thread: ");
	/* async: wait for new thread */
	sleep(1);
	exit(0);
}
