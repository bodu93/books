#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

#include <stdio.h>
#include <stdlib.h>

#define prlimits(name) pr_limits(#name, name)

static void pr_limits(const char* name, int resource) {
    struct rlimit limit;

    if (getrlimit(resource, &limit) < 0) {
        fprintf(stderr, "getrlimit error for %s\n", name);
        exit(1);
    }
    printf("%-14s  ", name);

    unsigned long long lim;
    if (limit.rlim_cur == RLIM_INFINITY) {
        printf("(infinite)  ");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld  ", lim);
    }

    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }
    
    putchar('\n');
} 

int main() {
#ifdef RLIMIT_AS
    prlimits(RLIMIT_AS);
#endif

#ifdef RLIMIT_CORE
    prlimits(RLIMIT_CORE);
#endif

#ifdef RLIMIT_CPU
    prlimits(RLIMIT_CPU);
#endif

#ifdef RLIMIT_DATA
    prlimits(RLIMIT_DATA);
#endif

#ifdef RLIMIT_FSIZE
    prlimits(RLIMIT_FSIZE);
#endif

#ifdef RLIMIT_MEMLOCK
    prlimits(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    prlimits(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    prlimits(RLIMIT_NICE);
#endif

#ifdef RLIMIT_NOFILE
    prlimits(RLIMIT_NOFILE);
#endif

#ifdef RLIMIT_NPROC
    prlimits(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
    prlimits(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
    prlimits(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
    prlimits(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    prlimits(RLIMIT_SIGPENDING);
#endif

#ifdef RLIMIT_STACK
    prlimits(RLIMIT_STACK);
#endif

#ifdef RLIMIT_SWAP
    prlimits(RLIMIT_SWAP);
#endif

#ifdef RLIMIT_VMEM
    prlimits(RLIMIT_VMEM);
#endif

    exit(0);
}
