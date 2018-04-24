#include "../include/apue.h"

#include <sys/socket.h>

#define MAXSLEEP 128

int connect_retry(int domain, int type, int protocol, const struct sockaddr* addr, socklen_t alen) {
	/*
	 * Try to connect with exponential backoff
	 */
	for (int numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		int fd;
		if ((fd = socket(domain, type, protocol)) < 0)
			return -1;

		if (connect(fd, addr, alen) == 0) {
			/*
			 * connection accepted.
			 */
			return fd;
		}
		close(fd);

		/*
		 * Delay before trying again.
		 */
		if (numsec <= MAXSLEEP / 2)
			sleep(numsec);
	}

	return -1;
}
