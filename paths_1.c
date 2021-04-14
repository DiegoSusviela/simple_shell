#include "header.h"

extern list_t *paths;

list_t *create_paths()
{
	char *path = _getenv("PATH"), *str1;
	int index = 0, count, largo;
	list_t *nodo, *head;

	nodo = malloc(sizeof(list_t));
	if (!nodo)
		return(NULL);
	nodo->next = NULL;
	head = nodo;
	while(path[index])
	{
		largo = 0;
		while(path[index + largo] && path[index + largo] != ':')
			largo++;
		str1 = malloc(sizeof(char) * (largo + 2));
		if (!safty_nets(str1, "p", head))
			return (0);
		count = 0;
		while(path[index] && path[index] != ':')
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

int check_paths(char **argv)
{
	list_t *path_aux = paths;
	struct stat stats;
	char *pathname, *tmp;

	while (path_aux)
	{
		pathname = _strdup(path_aux->str);
		if (!safty_nets(pathname, "a", argv))
			return (0);
		tmp = realloc(pathname, BUFFSIZE);
		if (!safty_nets(tmp, "ax", argv, pathname))
			return (0);
		pathname = tmp;
		_strcat(pathname, argv[0]);
		if (!stat(pathname, &stats))
			break;
		path_aux = path_aux->next;
		free(pathname);
	}
	if (!path_aux)
		pathname =	_strdup(argv[0]);

	if (fork() == 0)
		if (execve(pathname, argv, NULL) == -1)
			perror(argv[0]);
	wait(NULL);
	free(pathname);
	return (!safty_nets(NULL, "a", argv));
}