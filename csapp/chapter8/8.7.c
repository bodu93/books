#include "csapp.h"

unsigned int snooze(unsigned int secs) {
    unsigned int left_secs = sleep(secs);
    printf("\nSlept for %u of %u secs.\n", secs - left_secs, secs);
    return left_secs;
}

void sig_handler(int sig) {
    // do nothing
}

int main(int argc, char **argv) {
    if (argc < 2 && !atoi(argv[1])) {
        return 1;
    }

    signal(SIGINT, sig_handler);
    
    unsigned secs = (unsigned int)(atoi(argv[1]));
    snooze(secs);

    return 0;
}
