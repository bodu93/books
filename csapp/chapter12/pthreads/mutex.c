#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *a;
    double *b;
    double sum;
    int veclen;
} DOTDATA;

#define NUMTHRDS 4
#define VECLEN 1000000

DOTDATA dotstr;
pthread_t callThds[NUMTHRDS];
pthread_mutex_t mutexsum;

void *dotprod(void *arg) {
    long offset = (long)arg;
    int len = dotstr.veclen;

    int start = offset * len;
    int end = start + len;

    double *x = dotstr.a;
    double *y = dotstr.b;

    double mysum = 0;
    for (int i = start; i < end; i++) {
        mysum += (x[i] * y[i]);
    }

    pthread_mutex_lock(&mutexsum);
    dotstr.sum += mysum;
    printf("thread %ld did %d to %d: mysum = %f global sum = %f\n"
            , offset, start, end, mysum, dotstr.sum);
    pthread_mutex_unlock(&mutexsum);

    pthread_exit((void *)0);
}

int main() {
    double *a = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));
    double *b = (double *)malloc(NUMTHRDS * VECLEN * sizeof(double));

    for (int i = 0; i < VECLEN * NUMTHRDS; i++) {
        a[i] = 1;
        b[i] = a[i];
    }


    dotstr.veclen = VECLEN;
    dotstr.a = a;
    dotstr.b = b;
    dotstr.sum = 0;

    pthread_mutex_init(&mutexsum, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < NUMTHRDS; i++) {
        pthread_create(&callThds[i], &attr, dotprod, (void *)i);
    }

    pthread_attr_destroy(&attr);

    void *status = 0;
    for (int i = 0; i < NUMTHRDS; i++) {
        pthread_join(callThds[i], &status);
    }

    printf("sum = %f\n", dotstr.sum);
    free(a);
    free(b);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}
