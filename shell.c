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

void liberar_paths(list_t *list)
{
	list_t *aux = list->next;

	if (list)
	{
		free(list->str);
		free(list);
		liberar_paths(aux);
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
char *_getenv(const char *name)
{
	extern char ** environ;
	int i, c;
	size_t j;

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		c = strncmp(environ[i], name, j);
			if ( c == 0)
			{
				strtok(environ[i], "=");
				return(strtok(NULL, "="));
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
	char *path = _getenv("PATH");
	int index = 0, count, largo;
	char *str1;
	list_t *nodo;
	list_t *head;

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
		str1 = malloc(sizeof(char) * largo + 1);
		count = 0;
		while(path[index] && path[index] != ':')
		{
			str1[count] = path[index];
			index++;
			count++;
		}
		str1[count] = '/';
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
	return (head);
}

int *space_remover(char *to_remove)
{
	int pos_rem = 0, flag = 0, pos_cont = 0, count = 0;
	char *words;
	int *index;

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

char *take_input()
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
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
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
	char *pathname, *tmp, str2[] = "exit", *buffer, str3[] = "env";
	char **argv;
	list_t *path_aux = paths;
	
	buffer = take_input();
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
																			/*need to free paths*/
		if(argv[1])
			exit(atoi(argv[1]));
		exit(0);
	}
	if(!strcmp(argv[0], str3))
	{
		print_env();
		return (1);
	}
	while (path_aux)
	{
		pathname = strdup(path_aux->str);  								/*alloca pathname   3*/
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
		free(pathname);														/*libero pathname	3*/
	}
	if (path_aux)
	{
		if (fork() == 0)
			execve(pathname, argv, NULL);
		wait(NULL);
		free(pathname);														/*libero pathname	3*/
		liberar_argv(argv);													/*libero argv		2*/
		return (1);
	}
	liberar_argv(argv);														/*libero argv		2*/
	return (0);
}

void start_shell(list_t *paths)
{
	printf("$ ");
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
