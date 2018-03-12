#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

extern char** environ;

pthread_mutex_t env_mutex;		/* keep environ variable unchangeable when searching name-value pair */
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init() {
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char* name, char* buf, size_t buflen) {
	pthread_once(&init_done, thread_init);

	size_t len = strlen(name);
	pthread_mutex_lock(&env_mutex);
	for (int i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
				(environ[i][len] == '=')) {
			size_t valen = strlen(&environ[i][len + 1]);
			if (valen >= buflen) {
				pthread_mutex_unlock(&env_mutex);
				return ENOSPC;
			}
			strcpy(buf, &environ[i][len + 1]);
			pthread_mutex_unlock(&env_mutex);
			return 0;
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return ENOENT;
}
