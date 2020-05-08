#include "minish.h"
#include "builtins.h"

int globalstatret = 0;
void catch_ctrl_C(int);
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

int linea2argv(char *linea, int argc, char **argv)
{
    char *word, len = 0;
    word = *argv++ = strtok(linea, DELIMS); // falta ver lo de las comillas
    while (word != NULL && len <= argc)
    {
        len++;
        word = *argv++ = strtok(NULL, DELIMS); // falta ver lo de las comillas
    }
    return len;
}

int ejecutar(int argc, char **argv)
{
    struct builtin_struct *matched_struct = NULL;
    if ((matched_struct = builtin_lookup(argv[0])) != NULL)
        globalstatret = matched_struct->func(argc, argv);
    else
        globalstatret = externo(argc, argv);
    return globalstatret;
}

int externo(int argc, char **argv)
{
    printf("No encontre el comando\n");
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
    return;
}

void run(char *line, char argc, char **argv)
{
    char *res;
    while (1)
    {
        print_prompt();
        res = fgets(line, MAXLINE, stdin);
        argc = linea2argv(line, MAXWORDS, argv);
        if (res != NULL && argc > 0)
            ejecutar(argc, argv);
        else if (res == NULL)
            putchar('\n');
        argc = 0;
    }
}