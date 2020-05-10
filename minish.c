#include "minish.h"
#include "builtins.h"

int globalstatret = 0;
void run(char *, char, char **);

int main()
{
    struct sigaction act;
    char line[MAXLINE];
    char *argv[MAXWORDS];
    int argc = 0;

    sigaction(SIGINT, NULL, &act);
    act.sa_handler = catch_ctrl_C;
    sigaction(SIGINT, &act, NULL);

    run(line, argc, argv);
    return 0;
}

void print_prompt()
{
    char cwd[MAXCWD];
    getcwd(cwd, sizeof(cwd));
    char hostname[256];
    gethostname(hostname, (size_t)sizeof(hostname));
    char *user = getlogin();
    fprintf(stderr, "\033[0;36m%s@%s\033[0m:\033[01;33m%s\033[0m> ", user, hostname, cwd);
}

void catch_ctrl_C(int sig)
{
    putchar('\n');
    return;
}

void run(char *line, char argc, char **argv)
{
    char *res;
    char *home, minish_history_dir[MAXCWD];
    FILE *f;

    while (1)
    {
        print_prompt();
        res = fgets(line, MAXLINE, stdin);
        home = getenv("HOME");
        snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
        f = fopen(minish_history_dir, "a");
        if (f != NULL)
        {
            fprintf(f, "%s", line);
            fclose(f);
        }
        argc = linea2argv(line, MAXWORDS, argv);
        if (res != NULL && argc > 0)
            ejecutar(argc, argv);
        // else if (res == NULL)
        //     putchar('\n');
        argc = 0;
    }
}