#include "builtins.h"

int builtin_exit(int argc, char **argv)
{
    printf("Bye!\n");
    exit(atoi(argv[1]));
    return 0;
}