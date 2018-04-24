#ifndef APUE3E_LOG_H
#define APUE3E_LOG_H

#include "base.h"
#include <stdarg.h>

/*
 * caller must define and set this: nonzero if
 * interactive, zero if dameon
 */
extern int log_to_stderr;

/*
 * Print a message and return to caller
 * Caller specifies "errnoflag" and "priority"
 */
void log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap);

/*
 * Initialize syslog(), if running as dameon
 */
void log_open(const char *ident, int option, int facility);

/*
 * Nonfatal error related to a system call
 * Print a message with the system's errno value and return.
 */
void log_ret(const char *fmt, ...);

/*
 * Fatal error related to a system call.
 * Print a message and terminate
 */
void log_sys(const char *fmt, ...);

/*
 * Nonfatal error related to a system call
 * Print a message and return.
 */
void log_msg(const char *fmt, ...);

/*
 * Fatal error unrelated to a system call
 * Print a message and terminate
 */
void log_quit(const char *fmt, ...);

/*
 * Fatal error related to a system call
 * Error number passed as an explicit parameter.
 * Print a message and terminate.
 */
void log_exit(int error, const char *fmt, ...);

#endif /* APUE3E_LOG_H */
