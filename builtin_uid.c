#include "builtins.h"

int builtin_uid(int argc, char **argv)
{
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    if (pwd == NULL)
        return -1;
    else
        printf("Name: %s\t UID: %ld\n", pwd->pw_gecos, (long)pwd->pw_uid);
    return 0;
}