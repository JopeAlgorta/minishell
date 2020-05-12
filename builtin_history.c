#include "builtins.h"

void _qsort(char **, int, int);
void swap(char **, int, int);

int builtin_history(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("minish: %s: too many arguments", argv[0]);
        return -1;
    }
    else
    {
        int lines = 0;
        int linesToRead = 10;
        char *home, minish_history_dir[MAXCWD];
        FILE *f;
        char *lineptr[MAXLINES]; // pointers to text lines
        home = getenv("HOME");
        snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
        f = fopen(minish_history_dir, "r");
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
        _qsort(lineptr, 0, nlines - 1);

        while (linesToRead >= 0)
            printf("%s", lineptr[linesToRead--]);
        fclose(f);
        // free(lineptr);
    }
    return 0;
}

/* _qsort: sort v[left]...v[right] into increasing order */
void _qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) // do nothing if array contains fewer than two elements
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) > 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last - 1);
    _qsort(v, last + 1, right);
}
/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}