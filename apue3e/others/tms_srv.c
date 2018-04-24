#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/socket.h>

#define NQ          3               /* number of queues */
#define MAXMSZ      512             /* maximum message size */
#define KEY         0x123           /* key for first message queue */

struct threadinfo {
    int qid;
    int fd;
};

struct tmsg {
    long mytype;
    char mtext[MAXMSZ];
};

void* helper(void* arg) {
    struct threadinfo* tip = (struct threadinfo*)arg;

    int n;
    struct tmsg m;
    while (1) {
        memset(&m, 0, sizeof(m));
        if ((n = msgrcv(tip->qid, &m, MAXMSZ, 0, MSG_NOERROR)) < 0) {
            fputs("msgrcv error\n", stderr);
            exit(1);
        }
        if (write(tip->fd, m.mtext, n) < 0) {
            fputs("write error\n", stderr);
            exit(1);
        }
    }
}

int main() {
    int fd[2];
    struct pollfd pfd[NQ];
    struct threadinfo ti[NQ];
    pthread_t tid[NQ];
    int qid[NQ];
    for (int i = 0; i < NQ; i++) {
        if ((qid[i] = msgget((KEY + i), IPC_CREAT | 0666)) < 0) {
            fputs("msgget error\n", stderr);
            exit(1);
        }

        printf("queue ID %d is %d\n", i, qid[i]);

        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0) {
            fputs("socketpair error\n", stderr);
            exit(1);
        }

        pfd[i].fd = fd[0];
        pfd[i].events = POLLIN;
        ti[i].qid = qid[i];
        ti[i].fd = fd[1];
        int err;
        if ((err = pthread_create(&tid[i], NULL, helper, &ti[i])) != 0) {
            fputs("pthread_create error\n", stderr);
            exit(1);
        }
    }

    char buf[MAXMSZ];
    while (1) {
        if (poll(pfd, NQ, -1) < 0) {
            fputs("poll error\n", stderr);
            exit(1);
        }
        
        for (int i = 0; i < NQ; i++) {
            if (pfd[i].revents & POLLIN) {
                int n;
                if ((n = read(pfd[i].fd, buf, sizeof(buf))) < 0) {
                    fputs("read error\n", stderr);
                    exit(1);
                }
                buf[n] = 0;
                printf("queue id %d, message %s\n", qid[i], buf);
            }
        }
    }

    exit(0);
}
