#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include <stdio.h>
#include <stdlib.h>

char* userNameFromId(uid_t uid) {
    struct passwd* pwd;

    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t userIdFromName(const char* name) {
    if (name == NULL || *name == '\0') /* null or empty string */
        return -1;

    /* allow a numeric name string */
    char* endptr;
    uid_t u = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return u;

    struct passwd* pwd = getpwnam(name);
    return (pwd == NULL) ? -1 : pwd->pw_uid;
}

char* groupNameFromId(gid_t gid) {
    struct group* grp;
    
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char* name) {
    if (name == NULL || *name == '\0') /* null or empty name string */
        return -1;

    /* allow numeric name string */
    char* endptr;
    gid_t g = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return g;

    struct group* grp = getgrnam(name);
    return (grp == NULL) ? -1 : grp->gr_gid;
}

void idshow() {
    printf("\nruid: %u, euid: %u\n", getuid(), geteuid());
}

/* test for set-user-id root program */
int main() {
    idshow();
    //uid_t suid = getuid();
    //printf("suid = %u\n", suid);
    //setreuid(getuid(), getuid());
    /* setreuid(-1, getuid()); */
    setreuid(getuid(), getuid());
    idshow();
    //if (setreuid(getuid(), suid) < 0)
    //    fprintf(stderr, "%s error\n", "setreuid");
    /* setreuid(-1, 0); */
    setreuid(-1, 0);
    idshow();

    return 0;
}
