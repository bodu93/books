#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thd_func(void* arg) {
	printf("thread running...\n");

	return ((void*)1);
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thd_func, NULL);

	pthread_detach(tid);

	int err = pthread_join(tid, NULL);
	if (err != 0) {
		/* err == EINVAL: 22 */
		fprintf(stderr, "pthread_join error: %d\n", err);
	}

	/* exit(0) */
	return 0;
}
