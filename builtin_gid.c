#include "builtins.h"

int builtin_gid(int argc, char **argv)
{
    if (argc == 1)
    {
        gid_t gids[LIMITGROUPS];
        struct group *grp;
        int count;
        if ((count = getgroups(LIMITGROUPS, gids)) == -1) // Obtengo los grupos del usuario
        {
            perror("gid");
            return errno;
        }
        else
            for (int i = 0; i < count; i++)
                if ((grp = getgrgid(gids[i])) == NULL) // Se recorren y se imprimen
                {
                    perror("gid");
                    return errno;
                }
                else
                    printf("%s (%d)\n", grp->gr_name, (int)gids[i]);
        return 0;
    }
    else
    {
        fprintf(stderr, "dir: %s: too many arguments\n", argv[0]);
        return -1;
    }
}