#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4
#define N 1000
#define MEGEXTRA 1000000

pthread_attr_t attr;

void *doWork(void *thdid) {
    long tid = (long)thdid;

    size_t mystacksize;
    pthread_attr_getstacksize(&attr, &mystacksize);
    printf("thread %ld: stack size = %li bytes \n", tid, mystacksize);

    double A[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = ((i * j) / 3.452) + (N - i);
        }
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NTHREADS];
    
    pthread_attr_init(&attr);
    
    size_t stacksize;
    pthread_attr_getstacksize(&attr, &stacksize);
    printf("default stack size = %li\n", stacksize);
    stacksize = sizeof(double) * N * N + MEGEXTRA;
    printf("amount of stack needed per thread = %li\n", stacksize);

    pthread_attr_setstacksize(&attr, stacksize);
    printf("creating threads with stack size = %li bytes\n", stacksize);

    int t = 0;
    for (; t < NTHREADS; t++) {
        int rc = pthread_create(&threads[t], &attr, doWork, (void *)t);
        if (rc) {
            printf("error; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    printf("created %d threads.\n", t);
    pthread_exit(NULL);

}
