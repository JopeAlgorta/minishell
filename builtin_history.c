#include "builtins.h"

int builtin_history(int argc, char **argv)
{
    if (argc > 2)
    {
        errno = E2BIG; // Muchos argumentos
        {
            perror("history"); // Se probo una manera distinta de mandar un error.
            return errno;
        }
    }
    else
    {
        int linesToRead = 10; // Por defecto, inicializo las lineas a leer en 10
        char *home, minish_history_dir[MAXCWD], *lineptr[MAXLINES];
        FILE *f;
        if ((home = getenv(HOME)) == NULL)
        {
            perror("history");
            return errno;
        }
        snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
        if ((f = fopen(minish_history_dir, "r")) == NULL)
            return errno;
        if (argc > 1)
            linesToRead = atoi(argv[1]) - 1;
        char line[MAXLINE];
        int nlines = 0;
        char *p;
        while (fgets(line, MAXLINE, f) != NULL)
        {
            p = malloc(strlen(line));
            strcpy(p, line);
            lineptr[nlines++] = p;
//			free(p);
        }
        nlines--; // Decremento en uno el numero de lineas para posicionarme en el ultimo elemento del array
        while (nlines >= 0 && linesToRead >= 0)
            printf("%s", lineptr[nlines--]), linesToRead--;
        if (fclose(f) == EOF)
        {
            perror("history");
            return errno;
        }
    }
    return 0;
}
