#ifndef APUE3E_FLOCK_H
#define APUE3E_FLOCK_H

#include <unistd.h>

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);

#define read_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define un_lock(fd, offset, whence, len) \
	lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))


pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len);

#define is_read_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)

#define is_write_lockable(fd, offset, whence, len) \
	(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

#endif // APUE3E_FLOCK_H
