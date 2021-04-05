#include "header.h"

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


	argv = malloc(sizeof(char *) * largo(index));							/*we are not freeing this*/
	if (!argv)								/*check if reallocation was posible*/
	{
		printf("NO mem\n");
		return(0);
	}
	/*printf("%i\n", largo(index));*/
	for (cont = 0; cont < largo(index); cont++)
	{
		aux = &buffer[index[cont]];
		argv[cont] = malloc(sizeof(char) * largo_palabra(aux));				/*we are not freeing this*/
		/*printf("%i\n", largo_palabra(aux));*/
		iter = 0;
		while (buffer[index[cont] + iter])
		{
			argv[cont][iter] = buffer[index[cont] + iter];
			iter++;
		}
	}
	return (argv);
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

int validate_usr_in(char *usr_input)
{
	int pos = 0;

	while(usr_input[pos] && usr_input[pos] != ' ')
		pos++;
	if (usr_input[pos])
		return (0);
	return(1);
}




int *space_remover(char *to_remove)
{
	int pos_rem = 0, flag = 0, pos_cont = 0, count = 0;
	char *words;
	int *index;

	index = malloc(sizeof(int) * BUFFSIZE);
	/*word_container = malloc(sizeof(words) * amount_words(to_remove));*/
	/*word_container = malloc(BUFFSIZE);*/
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

int find_and_run_command()
{
	int pos = 0, i = 0, j = 0, k, *index;
	int amount_of_words = 0;
	struct stat stats;
	char *pathname, *tmp, str2[] = "exit", *buffer = NULL;
	char **word_container;
	char *aux;

	char *pathfinder[7][2] = {
		{"/usr/local/sbin/", NULL},
		{"/usr/local/bin/", NULL},
		{"/usr/sbin/", NULL},
		{"/usr/bin/", NULL},
		{"/sbin/", NULL},
		{"/bin/", NULL},
		{NULL, NULL}
	};
	ssize_t bufsize = 1024, readcount = 0;

	readcount = getline(&buffer, &bufsize, stdin);
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
	if (buffer[0] == '\0')
	{
		return (1);
	}


	index = space_remover(buffer);
	pos = 0;

	int iter = 1;
	amount_of_words++;
	while (index[iter])
	{
		iter++;
		amount_of_words++;
	}

	int iter2 = 0;
	char **argv;

	argv = ar(buffer, index);

/*
	while(index[iter2])
	{
		index[iter2] = 0;
		iter2++;
	}*/
	free(index);
	while (pathfinder[pos][0])
	{
		pathname = strdup(pathfinder[pos][0]);  /*Does a mnalloc 1 allocation each time it runs*/
		if (!pathname)							/*check if allocation was posible*/
		{
			printf("NO mem\n");
			return(0);
		}
		tmp = realloc(pathname, BUFFSIZE);
		if (!tmp)								/*check if reallocation was posible*/
		{
			printf("NO mem\n");
			return(0);
		}
		pathname = tmp;
		strcat(pathname, buffer);				/*appends the second string to the first*/
		if (!stat(pathname, &stats))
			break;
		pos++;
		free(pathname);							/*free in each while occurency, and if unkown command*/
	}
	if (!pathfinder[pos][0])
	{
		if(strcmp(buffer, str2))
		{
			free(buffer);
			return (0);
		}
		free(buffer);
		exit (99);
	}
	else
	{
		int toshi = 0;
		printf("pathname is %s\n", pathname);
		while (argv[toshi])
		{
			printf("argvs %i %s\n", toshi, argv[toshi]);
			toshi++;
		}
		

		if (fork() == 0)
			execve(pathname, argv, NULL);
		wait(NULL);
		free(pathname);							/*free in case command is found*/
		free(buffer);
		return (1);
	}
}

void start_shell(void)
{
	printf("$ ");
	if (!find_and_run_command())
		printf("Unkown command, error 98\n");
	start_shell();
}


int main()
{
	start_new_promtp();
	start_shell();
	return (1);
}
