#include "builtins.h"

int builtin_status(int argc, char **argv)
{
    printf("%d\n", globalstatret);
    return 0;
}