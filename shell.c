#include "header.h"
#include <limits.h>



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


char *take_user_input()
{
	ssize_t bufsize = 1024;
	char *buffer = NULL;
	ssize_t readcount = 0;
	int i = 0;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		printf("No mem, error 97\n");
		exit (97);
	}
	readcount = getline(&buffer, &bufsize, stdin);
	/*printf("%zu\n", bufsize);
	printf("%zu\n", strlen(buffer));*/
	if (readcount == -1)
	{
		free(buffer);
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
	/*printf("%zu\n", strlen(buffer));*/
	return (buffer);
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

/* /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin */


int find_and_run_command()
{
	int pos = 0;
	struct stat stats;
	char *pathname, str2[] = "exit";
	char *pathfinder[6][2] = {
		{"/usr/local/sbin/", NULL},
		{"/usr/local/bin/", NULL},
		{"/usr/sbin/", NULL},
		{"/usr/bin/", NULL},
		{"/sbin/", NULL},
		{"/bin/", NULL},
	};	
	ssize_t bufsize = 1024, readcount = 0;
	char *buffer = NULL;
	int i = 0;

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
	while (pathfinder[pos][0])
	{
		pathname = strdup(pathfinder[pos][0]);  /*Does a mnalloc 1 allocation each time it runs*/
		if (!pathname)							/*check if allocation was posible*/
		{
			printf("NO mem\n");
			return(0);
		}
		pathname = realloc(pathname, BUFFSIZE);
		if (!pathname)							/*check if reallocation was posible*/
		{
			printf("NO mem\n");
			return(0);
		}
		strcat(pathname, buffer);				/*appends the second string to the first*/
		if (!stat(pathname, &stats))
			break;
		pos++;
		free(pathname);
	}
	if (!pathfinder[pos][0])
	{
		free(pathname);
		if(strcmp(buffer, str2))
		{
			return (0);
		}
		exit (99);
	}
	else
	{
		if (fork() == 0)
			execve(pathname, pathfinder[pos], NULL);
		wait(NULL);
		free(pathname);
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
