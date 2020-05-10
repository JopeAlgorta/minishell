#include "builtins.h"

int builtin_history(int argc, char **argv)
{
    int lines = 0;
    int linesToRead = 10;
    char *home, minish_history_dir[MAXCWD];
    FILE *f;
    if (argc > 2)
    {
        printf("minish: %s: too many arguments", argv[0]);
        return -1;
    }
    else
    {
        home = getenv("HOME");
        snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
        f = fopen(minish_history_dir, "r");
        if (argc > 1)
            linesToRead = atoi(argv[1]);
        char line[MAXLINE];
        fseek(f, 0, SEEK_END);
        int cptr = ftell(f);
        cptr--;
        char c;
        while (cptr > 0)
        {
            c = fgetc(f);
            printf("%c", c);
            cptr--;
        }

        // while (lines < linesToRead)
        // {
        //     if (fgets(line, MAXLINE, f) != NULL)
        //     {
        //         lines++;
        //         printf("%s", line);
        //     }
        //     else
        //         break;
        // }
        fclose(f);
    }
    return 0;
}