#include "builtins.h"

int builtin_exit(int argc, char **argv)
{
    char c = argv[1];
    int i = c - '0';
    exit(i);
    return 0;
}