#include "header.h"

extern list_t *paths;

/**
 * safty_nets - safety nets
 * @checking: parameter to check
 * @str5: character to free
 *
 * Return: returns 1 if not found, 0 in success.
 *
 */

int safty_nets(char *checking, char *str5, ...)
{
	int pos = 0, pos1 = 0;
	va_list list;
	data_t type[] = {
			{'a', liberar_argv},
			{'p', liberar_paths},
			{'x', liberar_buffer},
			{'i', liberar_index},
			{'\0', NULL},
		};

	va_start(list, str5);
	if (!checking)
	{
		while (str5[pos])
		{
			pos1 = 0;
			while (type[pos1].type)
			{
				if (str5[pos] == type[pos1].type)
					type[pos1].func(list);
				pos1++;
			}
			pos++;
		}
		return (0);
	}
	return (1);
}

/**
 * liberar_argv - Function to free Argv
 * @list: list parameter
 *
 */

void liberar_argv(va_list list)
{
	int word_count = 0;
	char **argv = va_arg(list, char **);

	while (argv[word_count])
	{
		free(argv[word_count]);
		argv[word_count] = NULL;
		word_count++;
	}
	free(argv);
	argv = NULL;
}

/**
 * liberar_paths - Function to free Paths
 * @list: list parameter
 *
 */

void liberar_paths(va_list list)
{
	list_t *loc = va_arg(list, list_t *);
	list_t *aux;

	while (loc)
	{
		aux = loc->next;
		liberar_nodo(loc);
		loc = aux;
	}
}

/**
 * liberar_buffer - Function to free buffer
 * @list: list parameter
 *
 */

void liberar_buffer(va_list list)
{
	char *c = va_arg(list, char *);

	free(c);
}

/**
 * liberar_index - Function to free index
 * @list: list parameter
 *
 */
void liberar_index(va_list list)
{
	int *i = va_arg(list, int *);

	free(i);
}
