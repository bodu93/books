#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *vargp);

int main() {
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, thread, NULL);
    if (rc) {
        perror("pthread_create failed!\n");
        exit(-1);
    }

    pthread_join(tid, NULL);

    exit(0);
}

void *thread(void *vargp) {
    printf("hello world\n");
    return 0;
}
