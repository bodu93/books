#include "../include/error.h"

#include <errno.h>
#include <limits.h>
#include <unistd.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

/*
 * if OPEN_MAX is indeterminate, this might be inadequate.
 */
#define OPEN_MAX_GUESS 256

long
open_max() {
	if (openmax == 0) { /* first time throuth */
		errno = 0;
		if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
			if (errno == 0)
				openmax = OPEN_MAX_GUESS; /* we guess it! */
			else
				err_sys("sysconf error for _SC_OPEN_MAX");
		}
	}

	return openmax;
}
