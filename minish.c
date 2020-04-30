#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minish.h"
#include "builtins.h"

#define _BSD_SOURCE // definicion para evitar warning cuando se invoca a gethostname()
#define DELIMS " \n\t"

void print_prompt();

int main()
{
    char line[MAXLINE];
    char *argv[MAXWORDS];
    int argc = 0;
    while (1)
    {
        print_prompt();
        fgets(line, MAXLINE, stdin);
        argc = linea2argv(line, MAXWORDS, argv);
        if (argc != 0)
            ejecutar(argc, argv);
        argc = 0;
    }

    return 0;
}

int linea2argv(char *linea, int argc, char **argv)
{
    char *word, len = 0;
    word = *argv++ = strtok(linea, DELIMS);
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
    if ((matched_struct = builtin_lookup(argv[0])) != NULL) {
        printf("Encontre el comando\n"); 
        matched_struct->func(argc, argv);
    }
    else
        externo(argc, argv);
    return 0;
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
    char hostname[1024];
    gethostname(hostname, sizeof(hostname) - 1);
    char *user = getlogin();
    fprintf(stdout, "\033[0;36m%s@%s\033[0m:\033[01;33m%s\033[0m> ", user, hostname, cwd);
}