#include "builtins.h"

int builtin_history(int argc, char **argv)
{
    int lines = 0;
    char cwd[MAXCWD];
    getcwd(cwd, sizeof(cwd));
    FILE *f = fopen(strcat(cwd, HISTORY_FILE), 'r');
    if (argc > 2)
    {
        printf("minish: %s: too many arguments", argv[0]);
        return -1;
    }

    if (argc == 2)
    {
        char c;
        while (lines < argv[1])
        {
            if ((c = fgetc(f)) == '\n')
                lines++;
            printf("%c", c);
        }
    }
}