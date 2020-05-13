#include "builtins.h"

int builtin_history(int argc, char **argv)
{
    if (argc > 2)
    {
        errno = E2BIG; // Muchos argumentos
        perror("minish");
    }
    else
    {
        int linesToRead = 10; // Por defecto, inicializo las lineas a leer en 10
        char *home, minish_history_dir[MAXCWD], *lineptr[MAXLINES];
        FILE *f;
        if ((home = getenv("HOME")) == NULL)
            perror("minish");
        snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
        if ((f = fopen(minish_history_dir, "r")) == NULL)
            return -1;
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
        }
        nlines--; // Decremento en uno el numero de lineas para posicionarme en el ultimo elemento del array
        while (nlines >= 0 && linesToRead >= 0)
            printf("%s", lineptr[nlines--]), linesToRead--;
        if (fclose(f) == EOF)
            perror("minish");
    }
    return 0;
}