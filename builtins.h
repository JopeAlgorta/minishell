#define HELP_CD "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID "pid - muestra Process Id del minish"
#define HELP_SETENV "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID "uid - muestra nombre y número de usuario dueño del minish"

extern int builtin_exit(int argc, char **argv);
extern int builtin_help(int argc, char **argv);
extern int builtin_history(int argc, char **argv);
extern int builtin_status(int argc, char **argv);
extern int builtin_cd(int argc, char **argv);
extern int builtin_dir(int argc, char **argv);
extern int builtin_getenv(int argc, char **argv);
extern int builtin_gid(int argc, char **argv);
extern int builtin_setenv(int argc, char **argv);
extern int builtin_pid(int argc, char **argv);
extern int builtin_uid(int argc, char **argv);
extern int builtin_unsetenv(int argc, char **argv);

struct builtin_struct
{                              // struct con información de los builtins
    char *cmd;                 // nombre del comando builtin
    int (*func)(int, char **); // la función que lo ejecuta
    char *help_txt;            // el texto de ayuda
};

extern struct builtin_struct builtin_arr[];
extern struct builtin_struct *builtin_lookup(char *cmd);