#include "builtins.h"

int builtin_getenv(int argc, char **argv)
{
    char *cmd;
    for (int i = 1; i < argc; i++) // Por cada variable especificada se imprime su valor si existe.
        if ((cmd = getenv(argv[i])) != NULL)
            printf("%s=%s\n", argv[i], cmd);

    return 0;
}