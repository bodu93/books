#ifndef APUE3E_BASE_H
#define APUE3E_BASE_H

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#define MAXLINE 4096

/*
 * default file access permissions for new files.
 */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/*
 * default permissions for new directories
 */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

/* signal handlers */
typedef void Sigfunc(int);

#define min(a, b)	((a) < (b) ? (a) : (b))
#define max(a, b)	((a) > (b) ? (a) : (b))

#endif /* APUE3E_BASE_H */
