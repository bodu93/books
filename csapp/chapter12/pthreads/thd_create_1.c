#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *printHello(void *thd_arg) {
    printf("hello world!\n");

    return 0;
}

int main() {
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, printHello, NULL);
    
    printf("all threads created by main() are terminated.\n");
    /* By having main() explicitly call pthread_exit()
     * as the last thing it does, main() will block and
     * be kept alive to support the threads it created
     * until they are done. 
     */
    pthread_exit(NULL);

    return 0;
}
