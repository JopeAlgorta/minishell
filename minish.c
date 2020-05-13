#include "minish.h"
#include "builtins.h"

int globalstatret = 0;

int main()
{
    struct sigaction sigint_act;
    char line[MAXLINE];
    char *argv[MAXWORDS];
    int argc = 0;

    sigaction(SIGINT, NULL, &sigint_act);
    sigint_act.sa_handler = catch_ctrl_C;
    sigaction(SIGINT, &sigint_act, NULL);

	
    char *res;
    while (1)
    {
        print_prompt();
        res = fgets(line, MAXLINE, stdin); 
		append_history(line);
        argc = linea2argv(line, MAXWORDS, argv);
		if (res != NULL && argc > 0)
			if (ejecutar(argc, argv) == -1)
                perror("minish");
		argc = 0;
    }
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

void append_history(char *line)
{
    char *home, minish_history_dir[MAXCWD];
    FILE *f;
    int y, m, d, h, min, s;
    time_t now;
    struct tm *local;

    home = getenv("HOME");
    snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
    f = fopen(minish_history_dir, "a");
    if (f != NULL)
    {
        time(&now);
        local = localtime(&now);
        y = local->tm_year + 1900;
        m = local->tm_mon + 1;
        d = local->tm_mday;
        h = local->tm_hour;
        min = local->tm_min;
        s = local->tm_sec;
        fprintf(f, "%02d-%02d-%04d\t%02d:%02d:%02d\t%s", d, m, y, h, min, s, line);
        fclose(f);
    }
}
