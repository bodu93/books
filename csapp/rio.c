#include "rio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* allow signal hanlder interrupt
 * and this function will restart
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    char *bufp = (char *)usrbuf;
    
    while (nleft > 0) {
        ssize_t nread = 0;

        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) /* if interrupted by signal handler */
                nread = 0;
            else                /* or other errors, just return -1 like read */
                return -1;
        } else if (nread == 0)  /* EOF */
            break;

        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);
}


ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    char *bufp = (char *)usrbuf;

    while (nleft > 0) {
        ssize_t nwritten = 0;

        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }

        nleft -= nwritten;
        bufp += nwritten;
    }

    return n;
}




void rio_readinitb(rio_t *rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t refill_internal_buf(rio_t *rp) {
    while (rp->rio_cnt <= 0) {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0) {
            if (errno != EINTR) {
                return -1;
            }
        } else if (rp->rio_cnt == 0) {
            return 0;
        } else {
            rp->rio_bufptr = rp->rio_buf;
        }
    }

    return rp->rio_cnt;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
    ssize_t nread = refill_internal_buf(rp);
    if (nread <= 0) return nread;

    int cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;

    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
    char *bufp = (char *)usrbuf;
    char c;

    for (int n = 1; n < maxlen; ++n) {
        ssize_t rc = 0;

        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n') {
                ++n;
                break;
            }
        } else if (rc == 0) {           /* EOF */
            if (n == 1)
                return 0;
            else
                break;
        } else                          /* error */
            return -1;
    }

    *bufp = 0;
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n) {
    ssize_t nleft = n;
    char *bufp = (char *)usrbuf;

    while (nleft > 0) {
        ssize_t nread;
        /* errno set by read */
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
            return -1;
        /* EOF */
        else if (nread == 0)
            break;

        nleft -= nread;
        bufp += nread;
    }

    return (n - nleft);
}
