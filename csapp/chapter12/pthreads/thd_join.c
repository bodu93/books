#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void *busyWork(void *t) {
    long tid = (long)t;
    printf("thread %ld starting...\n", tid);

    double result = 0.0;
    for (int i = 0; i < 1000000; i++) {
       result = result + sin(i) * tan(i);
    }
    printf("thread %ld done. result = %e\n", tid, result);
    pthread_exit((void*)t);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("main: creating thread %d\n", i);
        int rc = pthread_create(&threads[i], &attr, busyWork, (void*)i);
        if (rc) {
            printf("error; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);


    void *status = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        int rc = pthread_join(threads[i], &status);
        if (rc) {
            printf("error; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("main: completed join with thread %d having a status of %ld\n", i, (long)status);
    }

    printf("mian: program completed. exiting.\n");
    pthread_exit(NULL);
}
