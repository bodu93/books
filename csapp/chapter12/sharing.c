#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define N 2
void *thread(void *vargp);

char **ptr;

int main() {
    pthread_t tid;

    char *msg[N] = {
        "hello from foo",
        "hello from bar"
    };

    ptr = msg;
    for (int i = 0; i < N; i++) {
        if (pthread_create(&tid, NULL, thread, (void *)i)) {
            perror("pthread_create failed\n");
            exit(-1);
        }
    }

    pthread_exit(NULL);
}

void *thread(void *vargp) {
    int myid = (int)vargp;
    static int cnt = 0;
    printf("[%d]: %s (cnt = %d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}
