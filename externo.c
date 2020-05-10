#include "minish.h"

int externo(int argc, char **argv)
{
    pid_t pid, wpid;
    int status;
    struct sigaction act;
    pid = fork();
    if (pid == 0)
    {
        // Proceso Hijo

        sigaction(SIGINT, NULL, &act);
        act.sa_handler = SIG_DFL;
        sigaction(SIGINT, &act, NULL);
        if (execvp(argv[0], argv) < 0)
            printf("minish: command '%s' not found\n", argv[0]);
    }
    else if (pid < 0) // Error haciendo el fork()
        perror("minish");
    else
    {
        // Proceso padre
        sigaction(SIGINT, NULL, &act);
        act.sa_handler = SIG_IGN;
        sigaction(SIGINT, &act, NULL);
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            if (wpid == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        sigaction(SIGINT, NULL, &act);
        act.sa_handler = catch_ctrl_C;
        sigaction(SIGINT, &act, NULL);
    }

    return 1;
}