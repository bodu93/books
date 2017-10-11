#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N 4

void *thread(void *vargp);

int main() {
    pthread_t tid[N];

    for (int i = 0; i < N; i++)
        pthread_create(&tid[i], NULL, thread, &i);
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    exit(0);
}

void *thread(void *vargp) {
    int myid = *(int *)vargp;
    printf("hello from thread %d\n", myid);
    return NULL;
}
