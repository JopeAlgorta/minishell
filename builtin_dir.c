#include "builtins.h"

struct tnode
{
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void freetree(struct tnode *);

int builtin_dir(int argc, char **argv)
{
    struct tnode *root;
    root = NULL;
    DIR *directory;
    struct dirent *dir;
    if ((directory = opendir(".")) != NULL) // "." es una referencia al directorio actual, entonces guardo en directory (que es un stream) la lista de archivos y carpetas de el directorio actual
    {
        errno = 0;                         // Se setea errno en 0 ya que readdir() retorna null en dos casos. El primero es cuando termina de leer todos los archivos y carpetas, que no es un error. El segundo es, si efectivamente existe un error entonces setea errno a otro valor distinto de cero.
        while ((dir = readdir(directory))) // Leo el directorio
        {
            if (argc > 1)
            {
                if (strstr(dir->d_name, argv[1])) // comparo lexicograficamente
                    root = addtree(root, dir->d_name);
            }
            else
                root = addtree(root, dir->d_name);
        }
        if (errno != 0) // Ocurre un error con readdir()
        {
            perror("dir");
            return errno;
        }
        treeprint(root);               // Se imprime el arbol
        if (closedir(directory) == -1) // Se cierra el directorio
        {
            perror("dir");
            return errno;
        }
    }
    else
    {
        perror("dir");
        return errno;
    }
    freetree(root);
    return 0;
}

struct tnode *talloc(void);
char *_strdup(char *);

/* Agregar nodo al arbol binario y asi ordenar la salida en orden alfabetico*/
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL)
    {
        p = talloc();
        p->word = _strdup(w);
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *_strdup(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

void freetree(struct tnode *p)
{
    if (p != NULL)
    {
        freetree(p->left);
		free(p->word);
		free(p);
        freetree(p->right);
    }
}















