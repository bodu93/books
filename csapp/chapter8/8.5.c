#include <stdio.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs) {
    unsigned int left_secs = sleep(secs);
    printf("Slept for %u of %u secs.\n", secs - left_secs, secs);
    return left_secs;
}
