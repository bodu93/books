#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXMSZ 512

struct tmsg {
    long mtype;
    char mtext[MAXMSZ];
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s KEY message\n", argv[0]);
        exit(1);
    }

    key_t key = strtol(argv[1], NULL, 0);
    long qid;
    if ((qid = msgget(key, 0)) < 0) {
        fprintf(stderr, "can't open queue key %s\n", argv[1]);
        exit(1);
    }

    struct tmsg m;
    memset(&m, 0, sizeof(m));
    strncpy(m.mtext, argv[2], MAXMSZ - 1);
    size_t nbytes = strlen(m.mtext);
    m.mtype = 1;
    if (msgsnd(qid, &m, nbytes, 0) < 0) {
        fprintf(stderr, "can't send message\n");
        exit(1);
    }

    exit(0);
}
