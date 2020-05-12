#include "builtins.h"

int builtin_setenv(int argc, char **argv)
{
    if (argc > 2)
        if (setenv(argv[1], argv[2], 1) == -1)
            perror("minish");
    return 0;
}