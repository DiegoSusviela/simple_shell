#include "header.h"

void liberar_buffer(va_list list)
{
	char *c = va_arg(list, char *);
	free(c);
}

void liberar_index(va_list list)
{
	int *i = va_arg(list, int *);
	free(i);
}

void liberar_pathname(char *pathname)
{
	free(pathname);
}

void liberar_argv(va_list list)
{
	int word_count = 0;
	char **argv = va_arg(list, char **);

	while(argv[word_count])
	{
		free(argv[word_count]);
		argv[word_count] = NULL;
		word_count++;
	}
	free(argv);
	argv = NULL;
}

void liberar_nodo(list_t *a_liberar)
{
	free(a_liberar->str);
	free(a_liberar);
}

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

static int safty_nets(char *checking, char *str5, ...)
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

void start_new_promtp(void)
{
	static int first_time = 1;
	const char *CLEAR_SCREEN_ANSI;

	if (first_time)
	{
		CLEAR_SCREEN_ANSI = " \033[1;1H\033[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 0;
	}
}
/*
ssize_t _getline(char **p_buffer, size_t *p_bufsize, stdin)
{
	int readcount = 0;

	return (readline);
}
*/

/*
char **copiar_path()
{
	extern char ** environ;
	char **ret;
	int i = 0, j = 0;

	while(environ[i])
	{
		while(environ[i][j])
		{
			ret[i][j] = environ[i][j];
			j++;
		}
		i++;
	}
}
*/

char *_getenv(const char *name)
{
	extern char ** environ;
	int i, cont = 0, pos = 0;
	size_t j;
	char *path;

	/*envi1 = copiar_env();*/
	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!strncmp(environ[i], name, j))
		{
			while(environ[i][j + cont])
				cont++;
			path = malloc(sizeof(char) * (cont + 1));
			if (!path)
				return (NULL);
			while(environ[i][j])
			{
				path[pos] = environ[i][j];
				pos++;
				j++;
			}
			path[pos] = '\0';
			return(path);
		}
	}
	return (NULL);
}


int largo(int *index)
{
	int ret = 1, pos = 1;
	while(index[pos])
	{
		ret++;
		pos++;
	}
	return (ret);
}

int largo_palabra(char *aux)
{
	int pos = 0, ret = 0;

	while(aux[pos])
	{
		pos++;
		ret++;
	}
	return (ret);
}


char **ar(char *buffer, int *index)
{
	char **argv, *aux;
	int cont = 0, iter;


	argv = malloc(sizeof(char *) * (largo(index) + 1));
	if (!argv)
		return(NULL);
	for (cont = 0; cont < largo(index); cont++)
	{
		aux = &buffer[index[cont]];
		argv[cont] = malloc(sizeof(char) * (largo_palabra(aux) + 1));
		if (!argv[cont])
		{
			while (cont >= 0)
			{
				free(argv[cont]);
				cont--;
			}
			return (NULL);
		}
		iter = 0;
		while (buffer[index[cont] + iter])
		{
			argv[cont][iter] = buffer[index[cont] + iter];
			iter++;
		}
		argv[cont][iter] = buffer[index[cont] + iter];
	}
	argv[cont] = NULL;
	return (argv);
}

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

int *space_remover(char *to_remove)
{
	int pos_rem = 0, pos_cont = 0, count = 0, *index;

	index = malloc(sizeof(int) * BUFFSIZE);
	if (!index)
		return(NULL);
	while (to_remove[pos_rem] == ' ')
	{
		to_remove[pos_rem] = '\0';
		pos_rem++;
	}
	while(to_remove[pos_rem])
	{
		index[pos_cont] = pos_rem;
		while (to_remove[pos_rem] !=  ' ' && to_remove[pos_rem])
			pos_rem++;
		while (to_remove[pos_rem] == ' ')
		{
			to_remove[pos_rem] = '\0';
			pos_rem++;
		}
		count++;
		pos_cont++;
	}
	index[pos_cont] = 0;
	return (index);
}

char *take_input(list_t *paths)
{
	char *buffer = NULL;
	size_t bufsize = 1024;
	ssize_t readcount = 0;
	int i = 0;

	readcount = getline(&buffer, &bufsize, stdin);
	if (!buffer)
		return (NULL);
	if (readcount == -1)
	{
		free(buffer);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		safty_nets(NULL, "p", paths);
		exit(0);
	}
	if (buffer[readcount - 1] == '\n' || buffer[readcount - 1] == '\t')
		buffer[readcount - 1] = '\0';
	while (buffer[i])
	{
		if (buffer[i] == '#' && buffer[i - 1] == ' ')
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
	return (buffer);
}

void print_env()
{
	int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}

int find_and_run_command(list_t *paths)
{
	int *index, ato;
	struct stat stats;
	char *pathname, *tmp, str2[] = "exit", *buffer, str3[] = "env", str4[] = "cd", **argv;
	list_t *path_aux = paths;
	char *home;

	buffer = take_input(paths);
	if (!safty_nets(buffer, "x", buffer))
		return (0);
	if (buffer[0] == '\0')
		return (!safty_nets(NULL, "x", buffer));
	index = space_remover(buffer);
	if (!index)
		return (safty_nets(NULL, "xi", buffer, index));
	if (buffer[0] == '\0' && !index[0])
		return (!safty_nets(NULL, "xi", buffer, index));
	argv = ar(buffer, index);
	if (!argv)
		return (safty_nets(NULL, "ix", index, buffer));
	safty_nets(NULL, "ix", index, buffer);

	if(!strcmp(argv[0], str2))
	{
		safty_nets(NULL, "p", paths);
		if(argv[1])
		{
			ato = atoi(argv[1]);
			safty_nets(NULL, "a", argv);
			exit(ato);
		}
		safty_nets(NULL, "a", argv);
		exit(0);
	}
	if(!strcmp(argv[0], str3))
	{
		print_env();
		return (!safty_nets(NULL, "a", argv));
	}
	if(!strcmp(argv[0], str4))
	{
		if (!argv[1])
		{
			home = _getenv("HOME");
			printf("%s\n", home);
			chdir(home);
		}
		else
			chdir(argv[1]);
		return (!safty_nets(NULL, "ax", argv, home));
	}

	if (!stat(argv[0], &stats))
		pathname = strdup(argv[0]);
	else
	{
		while (path_aux)
		{
			pathname = strdup(path_aux->str);
			if (!safty_nets(pathname, "a", argv))
				return (0);
			tmp = realloc(pathname, BUFFSIZE);
			if (!safty_nets(tmp, "ax", argv, pathname))
				return (0);
			pathname = tmp;
			strcat(pathname, argv[0]);
			if (!stat(pathname, &stats))
				break;
			path_aux = path_aux->next;
			free(pathname);
		}
	}
	if (path_aux)
	{
		if (fork() == 0)
			execve(pathname, argv, NULL);
		wait(NULL);
		free(pathname);
		return (!safty_nets(NULL, "a", argv));
	}
	perror(argv[0]);
	return (safty_nets(NULL, "a", argv));
}

void start_shell(list_t *paths)
{
	if (isatty(STDIN_FILENO))
		printf("(. Y .) ");
	if (!find_and_run_command(paths))
		printf("Unkown command, error 98\n");
	start_shell(paths);
}


int main()
{
	list_t *paths;
	paths = create_paths();
	if (!paths)
		printf("No mem to start shell\n");
	signal(SIGINT, SIG_IGN);
	start_new_promtp();
	start_shell(paths);
	return (1);
}
