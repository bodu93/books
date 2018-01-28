#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thr_fn1(void* arg) {
	printf("thread 1 running.\n");
	return ((void*)1);
}

void* thr_fn2(void* arg) {
	printf("thread 2 running.\n");
	pthread_exit((void*)2);
}

void* thr_fn3(void* arg) {
	printf("thread 3 running.\n");
	sleep(10);
	return ((void*)0);
}

void err_quit(const char* callname) {
	perror(callname);
	exit(1);
}

int main() {
	pthread_t tid1, tid2, tid3;

	int err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err < 0) err_quit("pthread_create");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0) {
		fprintf(stderr, "create thread 1 error: %d\n", err);
		exit(1);
	}

	err = pthread_create(&tid3, NULL, thr_fn3, NULL);
	if (err != 0) {
		fprintf(stderr, "create thread 2 error: %d\n", err);
		exit(1);
	}

	pthread_cancel(tid3);

	void* tret = NULL;
	err = pthread_join(tid3, &tret);

	printf("thread 3 exit with PTHREAD_CANCELED? %s\n",
			((long)tret == PTHREAD_CANCELED) ? "yes" : "no");

	err = pthread_join(tid1, &tret);
	printf("thread 1 exit code %ld\n", (long)tret);

	err = pthread_join(tid2, &tret);
	printf("thread 2 exit code %ld\n", (long)tret);

	exit(0);
}
