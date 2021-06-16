#include "builtins.h"

int builtin_pid(int argc, char **argv)
{
    if (argc == 1)
        printf("%s:\t%-4d\n", argv[0], getpid());
	else	
		return -1;
	return 0;
}
