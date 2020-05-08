#include "builtins.h"

int builtin_setenv(int argc, char **argv)
{
    if (argc > 2)
        return setenv(argv[1], argv[2], 1);
}