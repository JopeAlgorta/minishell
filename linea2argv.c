#include "minish.h"

int linea2argv(char *linea, int argc, char **argv)
{
    char *word, len = 0;
    word = *argv++ = strtok(linea, DELIMS);
	while (word != NULL && len < argc)
	{
        len++;
        word = *argv++ = strtok(NULL, DELIMS);
    }

	return len;
}
