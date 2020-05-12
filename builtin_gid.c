#include "builtins.h"

int builtin_gid(int argc, char **argv)
{
    if (argc == 1)
    {
        gid_t gids[LIMITGROUPS];
        struct group *grp;
        int count;
        count = getgroups(LIMITGROUPS, gids); // Obtengo los grupos del usuario
        if (count == -1)
            perror("minish");
        else
            for (int i = 0; i < count; i++)
                if ((grp = getgrgid(gids[i])) == NULL) // Se recorren y se imprimen
                    perror("minish");
                else
                    printf("%s (%d)\n", grp->gr_name, (int)gids[i]);
        return 0;
    }
    else
    {
        fprintf(stderr, "minish: %s: too many arguments\n", argv[0]);
        return -1;
    }
}