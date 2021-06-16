#include "builtins.h"

int builtin_help(int argc, char **argv)
{
    if (argc == 1)
    {
        struct builtin_struct *builtin_struct_ptr = NULL;
        builtin_struct_ptr = builtin_arr;
        while (builtin_struct_ptr->cmd != NULL)
        {
            printf("%s\n", builtin_struct_ptr->help_txt);
            builtin_struct_ptr++;
        }
    }
    else if (argc > 2)
    {
        perror("help");
        return errno;
    }
    else
    {
        struct builtin_struct *matched_struct;
        if ((matched_struct = builtin_lookup(argv[1])))
            printf("%s: %s\n", argv[1], matched_struct->help_txt);
        else
            printf("minish: %s: command %s does not exist \n", argv[0], argv[1]);
    }
    return 0;
}
