#include "minish.h"
#include "builtins.h"

int ejecutar(int argc, char **argv)
{
    struct builtin_struct *matched_struct = NULL;
    if ((matched_struct = builtin_lookup(argv[0])) != NULL)
        globalstatret = matched_struct->func(argc, argv);
    else
        globalstatret = externo(argc, argv);
    return globalstatret;
}