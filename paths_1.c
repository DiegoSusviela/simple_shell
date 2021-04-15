#include "header.h"

extern list_t *paths;
extern char *wopa;
extern int wopa2;

/**
 * create_paths - Function that creates the paths
 *
 * Return: a pointer to the head of the linked list
 *
 */

list_t *create_paths()
{
	char *path = _getenv("PATH"), *str1;
	int index = 0, count, largo;
	list_t *nodo, *head;

	nodo = malloc(sizeof(list_t));
	if (!nodo)
		return (NULL);
	nodo->next = NULL;
	head = nodo;
	while (path[index])
	{
		largo = 0;
		while (path[index + largo] && path[index + largo] != ':')
			largo++;
		str1 = malloc(sizeof(char) * (largo + 2));
		if (!safty_nets(str1, "p", head))
			return (0);
		count = 0;
		while (path[index] && path[index] != ':')
		{
			str1[count] = path[index];
			index++, count++;
		}
		str1[count] = '/';
		str1[count + 1] = '\0';
		nodo->str = str1;
		if (path[index])
		{
			nodo->next = malloc(sizeof(list_t));
			nodo = nodo->next;
			if (!nodo)
			{
				safty_nets(NULL, "p", head);
				return (NULL);
			}
			index++;
		}
		nodo->next = NULL;
	}
	free(path);
	return (head);
}

/**
 * check_paths - Function that checks all the paths
 * @argv: argument variable
 *
 * Return: Something
 *
 */

int check_paths(char **argv)
{
	list_t *path_aux = paths;
	struct stat stats;
	char *pathname;

	while (path_aux)
	{
		pathname = _strdup(path_aux->str);
		if (!safty_nets(pathname, "a", argv))
			return (0);
		_strcat(pathname, argv[0]);
		if (!stat(pathname, &stats))
			break;
		path_aux = path_aux->next;
		free(pathname);
	}
	if (!path_aux)
		pathname =	_strdup(argv[0]);

	if (fork() == 0)
	{
		if (execve(pathname, argv, NULL) == -1)
		{
			_puts(wopa);
			_puts(": ");
			_putchar(wopa2 + '0');
			_puts(": ");
			_puts(argv[0]);
			_puts(": not found");
			_putchar('\n');
		}
	}
	wait(NULL);
	free(pathname);
	return (!safty_nets(NULL, "a", argv));
}
