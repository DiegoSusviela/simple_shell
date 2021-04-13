#include "header.h"
#include "string_handlers.c"
#include "_strlen.c"

list_t *paths;

char **global_aliases = NULL;

char *previous_path;

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
/*
char **start_alias()
{
	int i = 0;
	char **hardcode = malloc(9 * sizeof(char *));

	hardcode[0] = strcpy("egrep='egrep --color=auto'");
	hardcode[1] = strcpy("fgrep='fgrep --color=auto'");
	hardcode[2] = strcpy("grep='grep --color=auto'");
	hardcode[3] = strcpy("l='ls -CF'");
	hardcode[4] = strcpy("la='ls -A'");
	hardcode[5] = strcpy("ll='ls -alF'");
	hardcode[6] = strcpy("ls='ls --color=auto'");
	hardcode[7] = NULL;

	return (hardcode);
}
*/
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

void liberar_arg_aux(char ***arg_aux)
{
	int pos = 0;

	while (arg_aux[pos])
	{
		safty_nets(NULL, "a", arg_aux[pos]);
		arg_aux[pos] = NULL;
		pos++;
	}
	free(arg_aux);
	arg_aux = NULL;
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

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j++;
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
/*
ssize_t _read(char *buffer)
{
	return ();
}*/

char *take_input()
{
	char *buffer = malloc(sizeof(char) * BUFFSIZE + 1);
	size_t bufsize = 1024;
	ssize_t readcount = 0;
	int i = 0;

	/*char *aux = malloc(sizeof(char) * BUFFSIZE);;

	_read(aux);
	printf("%s\n", aux);
	*/
	/*readcount = getline(&buffer, &bufsize, stdin);*/
	readcount = read(isatty(STDIN_FILENO), buffer, BUFFSIZE);
	/*printf("%zd\n", readcount);
	fflush(NULL);*/
	if (!buffer)
		return (NULL);
	if (readcount <= 0)
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
		if (buffer[0] == '#' || (buffer[i] == '#' && buffer[i - 1] == ' '))
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

void update_old_pwd()
{
	extern char ** environ;
	int i, pos2 = 0;
	size_t j;
	char *name = "OLDPWD=";
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j = 0;
			while (name[pos2])
			{
				environ[i][j] = name[pos2];
				pos2++, j++;
			}
			pos2 = 0;
			while (current_path[pos2])
			{
				environ[i][j] = current_path[pos2];
				j++, pos2++;
			}
			environ[i][j] = '\0';
		}
	}
}
void update_pwd()
{
	extern char ** environ;
	int i, pos2 = 0;
	size_t j;
	char *name = "PWD=";
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j = 0;
			while (name[pos2])
			{
				environ[i][j] = name[pos2];
				pos2++, j++;
			}
			pos2 = 0;
			while (current_path[pos2])
			{
				environ[i][j] = current_path[pos2];
				j++, pos2++;
			}
			environ[i][j] = '\0';
		}
	}
}

void salir(char **argv)
{
	int ato;

	safty_nets(NULL, "p", paths);
	if(argv[1])
	{
		ato = _atoi(argv[1]);
		safty_nets(NULL, "a", argv);
		exit(ato);
	}
	safty_nets(NULL, "a", argv);
	exit(0);
}

void env(char **argv)
{
	print_env();
	safty_nets(NULL, "a", argv);
}

void cd(char **argv)
{
	char *target, str5[] = "-";
	int flag = 0;

	if (!argv[1])
		target = _getenv("HOME");
	else
		if (!_strcmp(argv[1], str5))
		{
			target = _getenv("OLDPWD");
			printf("%s\n", target);
		}
		else
		{
			target = _strdup(argv[1]);
			flag = 1;
		}
	update_old_pwd();
	chdir(target);
	update_pwd();
	!safty_nets(NULL, "ax", argv, target);
}

int check_builtins(char **argv)
{
	int i = 0;

	builtins_t built[] = {
		{"exit", salir},
		{"env", env},
		{"cd", cd},
		/*{"setenv", setenv},
		{"unsetenv", unsetenv},*/
		{NULL, NULL}
	};
	fflush(NULL);

	while(built[i].f)
	{
		if (!_strcmp(argv[0], built[i].command))
			break;
		i++;
	}
	if (built[i].f)
	{
		built[i].f(argv);
		return (1);
	}
	return (0);
}

int check_paths(char **argv)
{
	list_t *path_aux = paths;
	struct stat stats;
	char *pathname, *tmp;
	printf("entro a los paths\n");

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

char ***separator(char **argv)
{
	int pos = 0, len = 0, pos1 = 0, pos2 = 0;
	char str1[] = ";";
	if (!_strcmp(argv[0], str1))
		return (NULL);

	char ***arg_aux = malloc(sizeof(char ***) * 150);
	char **sub_argv = malloc(sizeof(char **) * 250);

	pos = 0;
	while (argv[pos])
	{
		if (_strcmp(argv[pos], str1))
		{
			sub_argv[pos2] = _strdup(argv[pos]);
			pos2++;
		}
		else
		{
			sub_argv[pos2] = NULL;
			arg_aux[pos1] = sub_argv;
			if (argv[pos + 1])
				sub_argv = malloc(sizeof(char **) * 250);
			pos1++;
			pos2 = 0;
		}
		pos++;
	}
	sub_argv[pos2] = NULL;
	arg_aux[pos1] = sub_argv;
	arg_aux[pos1 + 1] = NULL;
	return (arg_aux);
}

int find_and_run_command()
{
	int *index, ato, flag, pos1 = 0;
	char *pathname, *tmp, str2[] = "exit", *buffer, str3[] = "env", str4[] = "cd", str5[] = "-", **argv;

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

	char ***arg_aux;

	arg_aux = separator(argv);							/*separator not done*/
	if (!arg_aux)
		printf("syntax error\n");

	fflush(NULL);
	
	int test = 0, i = 0;
	while (arg_aux[test])
	{
		i = 0;
		while (arg_aux[test][i])
		{
			printf("%s\n", arg_aux[test][i]);
			fflush(NULL);
			i++;
		}
		test++;
	}

	fflush(NULL);
	while (arg_aux[pos1])
	{
		if (!check_builtins(arg_aux[pos1]))
			check_paths(arg_aux[pos1]);
		pos1++;
		printf("se rompe aca 2\n");
		fflush(NULL);
	}
	liberar_arg_aux(arg_aux);
	return (1);
}

void start_shell()
{
	if (isatty(STDIN_FILENO))
		write(1, "(. Y .) ", 8);
	fflush(NULL);
	find_and_run_command(paths);
	start_shell(paths);
}

int main()
{
	paths = create_paths();
	/*global_aliases = start_alias();*/
	if (!paths)
		printf("No mem to start shell\n");
	signal(SIGINT, SIG_IGN);
	start_new_promtp();
	start_shell(paths);
	return (1);
}
