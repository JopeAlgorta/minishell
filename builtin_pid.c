#include "builtins.h"

int builtin_pid(int argc, char **argv)
{
    if (argv[1] && strcmp(argv[1], HELPOPT) == 0)
        printf("%s\n", HELP_PID);
    else if (argv[1])
        printf("%s: invalid option -- %s\nTry '%s --help' for more information.\n", argv[0], argv[1], argv[0]);
    else
        printf("PID:\t%-4d\n", getpid());
}