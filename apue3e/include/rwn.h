#ifndef APUE3E_RWN_H
#define APUE3E_RWN_H

#include <stdlib.h>
#include <unistd.h>

ssize_t readn(int fd, void* buf, size_t nbytes);
ssize_t writen(int fd, void* buf, size_t nbytes);

#endif // APUE3E_RWN_H
