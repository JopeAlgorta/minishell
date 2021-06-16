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
#include <limits.h>
#include <dirent.h>
#include <time.h>

#define MAXLINE 1024                   // tamaño máximo de la línea de entrada
#define MAXCWD 1024                    // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256                   // cantidad máxima de palabras en la línea
#define HISTORY_FILE ".minish_history" // nombre del archivo que almacena historia de comandos

#define HOME "HOME"
#define OLDPWD "OLDPWD"

#define DELIMS " \n\t" // delimitadores de argumentos para argv

/*
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

#define MAXARG 100
*/
// Variables
extern int globalstatret; // guarda status del ultimo comando - deberá definirse en el main

// Funciones
extern int ejecutar(int argc, char **argv);
extern int externo(int argc, char **argv);
extern int linea2argv(char *linea, int argc, char **argv);
void catch_ctrl_C(int);             // Manejador de SIGINT
extern void print_prompt();         // imprime el prompt string
extern void append_history(char *); // registra el comando ejecutado en el archivo ~/.minish_history

/*
    builtin_arr es una lista de los builtins, que se recorrerá en forma lineal.
    Podría usarse una estructura que mejorara la velocidad de búsqueda, pero
    en este ejercicio una lista que se recorre en forma lineal es suficiente.
    Deberá definirse e inicializarse como variable global, de esta manera:
    struct builtin_struct builtin_arr[] = {
        { "cd", builtin_cd, HELP_CD },
        .... etc. etc.
        { "uid", builtin_uid, HELP_UID },
        { NULL, NULL, NULL }
    };
    La definición no puede hacerse en este archivo minish.h porque está pensado
    para ser incluido en todos los fuentes y no se puede definir el mismo array en
    diferentes fuentes de un mismo programa.
*/

/*
    La siguiente lista de constantes de texto puede adaptarse/mejorarse, se pone como ejemplo.
    Lo lógico sería que estuvieran definidas en el mismo fuente que define el array builtin_arr
    en lugar de estar en este archivo .h.
*/
