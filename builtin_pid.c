#include "builtins.h"

int builtin_pid(int argc, char **argv)
{
    if (argc == 1)
        printf("PID:\t%-4d\n", getpid());
}