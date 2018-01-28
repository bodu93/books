#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void cleanup(void* arg) {
	printf("cleanup: %s\n", (char*)arg);
}

void* thd_func1(void* arg) {
	printf("thread 1 start...\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	if (arg)
		return ((void*)1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return ((void*)1);
}

void* thd_func2(void* arg) {
	printf("thread 2 start...\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	/*
	 * on my macOS, a bus error occurs when executed this line
	 * but on ubuntu14.04, no error occurs
	 *
	 * apue3e said that: In Single UNIX Specification,
	 * if a function call returned between pthread_cleanup_push and
	 * pthread_cleanup_pop, it is undefined.
	 * */
	if (arg)
		pthread_exit((void*)2);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void*)2);
}

void* thd_func3(void* arg) {
	printf("thread 3 start...\n");
	pthread_cleanup_push(cleanup, "thread 3 first handler");
	pthread_cleanup_push(cleanup, "thread 3 second handler");
	printf("thread 3 push complete\n");
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(1);
	pthread_exit((void*)3);
}


int main() {
	pthread_t tid1, tid2, tid3;
	int err;

	err = pthread_create(&tid1, NULL, thd_func1, (void*)1);
	if (err != 0 ) exit(1);

	err = pthread_create(&tid2, NULL, thd_func2, (void*)2);
	if (err != 0 ) exit(1);

	/*err = pthread_create(&tid3, NULL, thd_func3, (void*)3);*/
	/*if (err != 0 ) exit(1);*/

	err = pthread_join(tid1, NULL);
	if (err != 0 ) exit(1);

	err = pthread_join(tid2, NULL);
	if (err != 0) exit(1);

	/*pthread_join(tid3, NULL);*/
	/*if (err != 0) exit(1);*/

	exit(0);
}
