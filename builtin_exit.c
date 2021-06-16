#include "builtins.h"

int builtin_exit(int argc, char **argv)
{
  printf("Bye!\n");
  if (argc > 1)
    exit(atoi(argv[1])); // Hago un exit con el numero especificado
  else
    exit(1); // Por defecto exit 1
  return 0;
}
