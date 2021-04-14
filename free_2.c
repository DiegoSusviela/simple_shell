#include "header.h"

extern list_t *paths;

void liberar_nodo(list_t *a_liberar)
{
	free(a_liberar->str);
	free(a_liberar);
}

void liberar_pathname(char *pathname)
{
	free(pathname);
}

void liberar_arg_aux(char ***arg_aux, int pos)
{
	while (arg_aux[pos])
	{
		safty_nets(NULL, "a", arg_aux[pos]);
		arg_aux[pos] = NULL;
		pos++;
	}
}
