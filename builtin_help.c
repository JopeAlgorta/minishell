#include "builtins.h"

int builtin_help(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("minish: %s: not enough arguments\n", argv[0]);
        return -1;
    }
    else if (argc > 2)
    {
        printf("minish: %s: too many arguments\n", argv[0]);
        return -1;
    }
    else
    {
        struct builtin_struct *matched_struct;
        if ((matched_struct = builtin_lookup(argv[1])))
        {
            printf("%s: %s\n", argv[1], matched_struct->help_txt);
            return 0;
        }
        else
        {
            printf("minish: %s: command %s does not exist \n", argv[0], argv[1]);
            return -1;
        }
    }
}