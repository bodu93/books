#include "../include/log.h"

#include <errno.h>	/* for definition of errno */
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap) {
	char buf[MAXLINE];

	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	if (errnoflag)
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));

	strcat(buf, "\n");
	if (log_to_stderr) {
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	} else {
		syslog(priority, "%s", buf);
	}
}

void
log_open(const char *ident, int option, int facility) {
	if (log_to_stderr == 0)
		openlog(ident, option, facility);
}

void
log_ret(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
}

void
log_sys(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, errno, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}

void
log_msg(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
}

void
log_quit(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	log_doit(0, 0, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}

void
log_exit(int error, const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	log_doit(1, error, LOG_ERR, fmt, ap);
	va_end(ap);
	exit(2);
}
