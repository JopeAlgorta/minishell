#include "builtins.h"

int builtin_getenv(int argc, char **argv)
{
    char *cmd;
    if (argc > 1)
        if ((cmd = getenv(argv[1])) != NULL)
        {
            printf("%s=%s\n", argv[1], cmd);
            return 0;
        }
    return -1;
}