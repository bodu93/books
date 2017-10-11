#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *printHello(void *thdid) {
    long tid;
    tid = (long)thdid;
    printf("hello world! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("in main: creating thread %d\n", i);
        int rc = pthread_create(&threads[i], NULL, printHello, (void *)i);
        if (rc) {
            printf("error; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
