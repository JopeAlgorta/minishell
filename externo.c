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
        sigaction(SIGINT, NULL, &act); // El proceso hijo tratara la señal SIGINT con su
        act.sa_handler = SIG_DFL;      // comportamiento normal.
        sigaction(SIGINT, &act, NULL);

        if (argc > 0 && execvp(argv[0], argv) < 0)
			printf("minish: command '%s' not found\n", argv[0]);
	}
    else if (pid < 0) // Error haciendo el fork()
    {
        perror("fork error");
        return errno;
    }
    else
    {
        // Proceso padre
        sigaction(SIGINT, NULL, &act); // Cambio tratamiento de señal SIGINT
        act.sa_handler = SIG_IGN;      // para que el minish la ignore.
        sigaction(SIGINT, &act, NULL);

        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            if (wpid == -1)
            {
                perror("waitpid");
                return errno;
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        sigaction(SIGINT, NULL, &act); // Cambio tratamiento de señal SIGINT para
        act.sa_handler = catch_ctrl_C; // que no mate el proceso del minish.
        sigaction(SIGINT, &act, NULL);
    }

    return errno;
}
