#include "header.h"



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

	char *pathfinder[7][4] = {
		{"/usr/local/sbin/", NULL, NULL, NULL},
		{"/usr/local/bin/", NULL, NULL, NULL},
		{"/usr/sbin/", NULL, NULL, NULL},
		{"/usr/bin/", NULL, NULL, NULL},
		{"/sbin/", NULL, NULL, NULL},
		{"/bin/", NULL, NULL, NULL},
		{NULL, NULL, NULL, NULL}
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


	index = space_remover(buffer);
	pos = 0;

	int iter = 1;
	amount_of_words++;
	while (index[iter])
	{
		iter++;
		amount_of_words++;
	}
	char arguments[100], *dirs;
	int iter2 = 0, flag = 0;
	int start, count, pos_dir, am_dir = 0;
	char directorios[20][100];

	if (amount_of_words > 1)
	{
		start = 1;
		pos_dir = 0;
		am_dir = 0;
		for (iter = 1; iter < amount_of_words; iter++)
		{
			count = 0;
			pos_dir = 0;
	
			if (buffer[index[iter]] == '-' && buffer[index[iter] + 1] && buffer[index[iter] + 1] != ' ')
			{
				if (flag == 0)
				{
					flag = 1;
					arguments[0] = '-';
				}
				count++;
				while (buffer[index[iter] + count])
				{
					arguments[start] = buffer[index[iter] + count];
					start++;
					count++;
				}
				arguments[start] = '\0';
			}
			else
			{
				while (buffer[index[iter] + count])
				{
					directorios[am_dir][pos_dir] = buffer[index[iter] + count];
					pos_dir++;
					count++;
				}
				directorios[am_dir][pos_dir] = '\0';
				am_dir++;
			}				
		}
		printf("%s\n", arguments);
		printf("%i\n", am_dir);
	}
	printf("%s\n", arguments);
	while(index[iter2])
	{
		index[iter2] = 0;
		iter2++;
	}
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
		printf("%i\n", flag);
		if (flag = 1)
			pathfinder[pos][1] = arguments;
		/*pathfinder[pos][2] = directorios;*/
		int count_dirs;
		printf("%i\n", am_dir);
		if (am_dir > 0)
			for (count_dirs = 0; count_dirs < am_dir; count_dirs++)
			{
				pathfinder[pos][2] = directorios[count_dirs];
				if (fork() == 0)
					execve(pathname, pathfinder[pos], NULL);
				wait(NULL);
			}
		else
		{
			if (fork() == 0)
				execve(pathname, pathfinder[pos], NULL);
			wait(NULL);
		}
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
