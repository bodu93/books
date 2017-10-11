#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *thread(void *vargp);

volatile long cnt = 0;
sem_t mutex;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s <niters>\n", argv[0]);
        exit(0);
    }

    long niters = atoi(argv[1]);
    sem_init(&mutex, 0, 1);

    pthread_t tid1, tid2;
    int rc = pthread_create(&tid1, NULL, thread, &niters);
    rc = pthread_create(&tid2, NULL, thread, &niters);    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (cnt != (2 * niters))
        printf("BOOM! cnt = %ld\n", cnt);
    else
        printf("OK cnt = %ld\n", cnt);

    exit(0);
}

void *thread(void *vargp) {
    long niters = *(long *)vargp;

    for (int i = 0; i < niters; i++) {
        sem_wait(&mutex);
        cnt++;
        sem_post(&mutex);
    }

    return 0;
}
