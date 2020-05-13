#include "builtins.h"

int builtin_cd(int argc, char **argv)
{
    char cwd[MAXCWD], *home, *oldpwd;
    int status;
    if (getcwd(cwd, sizeof(cwd)) == NULL) // Obtengo directorio actual
    {
        perror("cd");
        return errno;
    }
    if (argc > 2)
    {
        printf("minish: %s: too many arguments\n", argv[0]);
        return -1;
    }
    else if (argc == 1) // solo un argumento significa ir al directorio de la variable $HOME
    {
        if (setenv("OLDPWD", cwd, 1) == -1) // seteo $OLDPWD en el directorio actual
        {
            perror("cd");
            return errno;
        }
        if ((home = getenv("HOME")) == NULL)
        {
            perror("cd");
            return errno;
        }
        status = chdir(home); // Cambio a directorio $HOME
    }
    else if (strcmp(argv[1], "-") == 0) // "cd -"  significa ir al directorio anterior al actual
    {
        if ((oldpwd = getenv("OLDPWD")) == NULL) // Obtengo el valor de $OLDPWD
        {
            perror("cd");
            return errno;
        }
        if ((status = chdir(oldpwd)) == -1) // Cambio al directorio anterior al actual
        {
            perror("cd");
            return errno;
        }
        printf("%s\n", oldpwd);             //
        if (setenv("OLDPWD", cwd, 1) == -1) // Guardo el directorio, ahora anterior, en $OLDPWD
        {
            perror("cd");
            return errno;
        }
    }
    else
    {
        if (setenv("OLDPWD", cwd, 1) == -1) // "cd xxx" cambia al directorio especificado en el primer argumento
        {
            perror("cd");
            return errno;
        }
        status = chdir(argv[1]);
    }
    if (status != 0)
        perror("cd");
    return status;
}
