#include "header.h"

void liberar_argv(char **argv)
{
	int word_count = 0, str_len = 0;

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

void liberar_paths(list_t *head)
{
	list_t *loc = head;
	list_t *aux;

	while (loc)
	{
		aux = loc->next;
		liberar_nodo(loc);
		loc = aux;
	}
}

char *find_path(char **env)
{
	/*
	char *path = "PATH=";
	unsigned int i = 0, j;

	while(env[i])
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
		i++;
	}
	return (env[i]);
	*/
}

void start_new_promtp(void)
{
	static int first_time = 1;
	const char *CLEAR_SCREEN_ANSI;

	if (first_time)
	{
		CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
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
	int i, c, cont = 0, pos = 0;
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
			path = malloc(sizeof(char) * (cont + 1));								/*safety net needed and later to free*/
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


	argv = malloc(sizeof(char *) * (largo(index) + 1));								/*we are not freeing this*/
	if (!argv)
	{
		printf("NO mem\n");
		return(0);
	}
	for (cont = 0; cont < largo(index); cont++)
	{
		aux = &buffer[index[cont]];
		argv[cont] = malloc(sizeof(char) * (largo_palabra(aux) + 1));				/*we are not freeing this, we need to add this safty net, but im lazy*/
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

	nodo = malloc(sizeof(list_t));							/*we are not freeing this*/
	if (!nodo)
	{
		printf("NO mem\n");
		return(NULL);
	}
	nodo->next = NULL;
	head = nodo;
	while(path[index])
	{
		largo = 0;
		while(path[index + largo] && path[index + largo] != ':')
			largo++;
		str1 = malloc(sizeof(char) * (largo + 2));
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
			nodo->next = malloc(sizeof(list_t));							/*we are not freeing this*/
			nodo = nodo->next;
			if (!nodo)
			{
				printf("NO mem\n");
				return(NULL);
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
	int pos_rem = 0, flag = 0, pos_cont = 0, count = 0, *index;
	char *words;

	index = malloc(sizeof(int) * BUFFSIZE);
	if (!index)
	{
		printf("NO mem\n");
		return(NULL);
	}
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

char *take_input(list_t *paths, char** argv)
{
	char *buffer = NULL;
	ssize_t bufsize = 1024, readcount = 0;
	int i = 0;

	readcount = getline(&buffer, &bufsize, stdin);							/*alloc  buffer    0*/
	if (!buffer)
	{
		printf("NO mem\n");
		return(0);
	}
	if (readcount == -1)
	{
		free(buffer);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		liberar_paths(paths);
		liberar_argv(argv);
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
	{
		printf("%s\n", environ[i]);
	}
}

int find_and_run_command(list_t *paths)
{
	int pos = 0, *index;
	struct stat stats;
	char *pathname, *tmp, str2[] = "exit", *buffer, str3[] = "env", **argv;
	list_t *path_aux = paths;
	
	buffer = take_input(paths, argv);
	if (buffer[0] == '\0')
		return (1);
	index = space_remover(buffer);											/*alloc index       1*/
	if (!index)
	{
		printf("NO mem\n");
		free(buffer);														/*libero buffer     0*/
		return(0);
	}
		if (buffer[0] == '\0' && !index[0])
		return (1);
	argv = ar(buffer, index);												/*alloc argv 		2*/
	free(index);															/*libero index      1*/
	free(buffer);															/*libero buffer     0*/
	if (!argv)
	{
		printf("NO mem\n");
		return(0);
	}
	if(!strcmp(argv[0], str2))
	{
		liberar_paths(paths);													/*need to free paths*/
		if(argv[1])
		{
			liberar_argv(argv);
			exit(atoi(argv[1]));
		}
		liberar_argv(argv);
		exit(0);
	}
	if(!strcmp(argv[0], str3))
	{
		liberar_argv(argv);
		print_env();
		return (1);
	}
	if (!stat(argv[0], &stats))
		pathname = argv[0];
	else
	{
		while (path_aux)
		{
			pathname = strdup(path_aux->str);  									/*alloca pathname   3*/
			if (!pathname)
			{
				printf("NO mem\n");
				liberar_argv(argv);												/*libero argv		2*/
				return(0);
			}
			tmp = realloc(pathname, BUFFSIZE);
			if (!tmp)
			{
				printf("NO mem\n");
				liberar_argv(argv);												/*libero argv		2*/
				free(pathname);													/*libero pathname	3*/
				return(0);
			}
			pathname = tmp;
			strcat(pathname, argv[0]);											/*appends the second string to the first*/
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
		/*if (&pathname != &argv[0])
			free(pathname);*/
		liberar_argv(argv);													/*libero argv		2*/
		return (1);
	}
	liberar_argv(argv);												/*libero argv		2*/
	return (0);
}

void start_shell(list_t *paths)
{
	printf("(. Y .) ");
	if (!find_and_run_command(paths))
		printf("Unkown command, error 98\n");
	start_shell(paths);
}


int main()
{
	list_t *paths;

	paths = create_paths();
	start_new_promtp();
	start_shell(paths);
	return (1);
}
