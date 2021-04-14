#include "header.h"

extern list_t *paths;

/**
 * liberar_nodo - safety nets
 * @a_liberar: parameter to check
 *
 * Return: returns 1 if not found, 0 in success.
 *
 */

void liberar_nodo(list_t *a_liberar)
{
	free(a_liberar->str);
	free(a_liberar);
}

/**
 * liberar_pathname - safety nets
 * @pathname: parameter to check
 *
 * Return: returns 1 if not found, 0 in success.
 *
 */

void liberar_pathname(char *pathname)
{
	free(pathname);
}

/**
 * liberar_arg_aux - safety nets
 * @arg_aux: parameter to check
 * @pos: kjlands
 *
 * Return: returns 1 if not found, 0 in success.
 *
 */

void liberar_arg_aux(char ***arg_aux, int pos)
{
	while (arg_aux[pos])
	{
		safty_nets(NULL, "a", arg_aux[pos]);
		arg_aux[pos] = NULL;
		pos++;
	}
}
