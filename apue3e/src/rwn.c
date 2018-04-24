#include "../include/rwn.h"

ssize_t readn(int fd, void* ptr, size_t n) {
	size_t nleft = n;
	ssize_t nread = 0;

	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return -1; /* error, return -1 */
			else
				break;	/* error, return amount read so far */
		} else if (nread == 0) {
			break; /* eof */
		}
		nleft -= nread;
		ptr += nread;
	}

	return n - left;
}

ssize_t writen(int fd, const void* ptr, size_t n) {
	size_t nleft = n;
	ssize_t nwritten = 0;

	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return -1; /* error, return -1 */
			else
				break; /* error, return amount written so far */
		} else if (nwritten == 0) {
			break; /* length of fd equals zero */
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

	return n - nleft;
}
