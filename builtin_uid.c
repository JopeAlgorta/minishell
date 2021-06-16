#include "builtins.h"

int builtin_uid(int argc, char **argv)
{
    struct passwd *pwd;
    errno = 0; // Se setea en 0 para saber si getpwuid da un error interno o si no encontro el  passwd del uid.
    if (argc > 0 && (pwd = getpwuid(getuid())) != NULL)
        printf("Name: %s\t %s: %ld\n", pwd->pw_gecos, argv[0], (long)pwd->pw_uid);
    else
    {
        perror("uid");
        return errno;
    }
    return 0;
}
