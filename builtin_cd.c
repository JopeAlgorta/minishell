#include "builtins.h"

int builtin_cd(int argc, char **argv)
{
    char cwd[MAXCWD];
    int status;
    getcwd(cwd, sizeof(cwd));
    if (argc > 2)
        printf("minish: %s: too many arguments\n", argv[0]);
    else if (argc == 1)
    {
        setenv("OLDPWD", cwd, 1);
        status = chdir(getenv("HOME"));
    }
    else
    {
        if (strcmp(argv[1], "-") == 0)
        {
            status = chdir(getenv("OLDPWD"));
            printf("%s\n", getenv("OLDPWD"));
            setenv("OLDPWD", cwd, 1);
        }
        else
        {
            setenv("OLDPWD", cwd, 1);
            char *newCWD[MAXCWD];
            snprintf(newCWD, MAXCWD, "%s/%s", cwd, argv[1]);
            status = chdir(newCWD);
            if (status == -1)
                printf("minish: %s: %s: No such file or directory\n", argv[0], argv[1]);
        }
    }

    return status;
}