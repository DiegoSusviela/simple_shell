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
	/*[] = "/bin/", pathname2[] = "/usr/bin/", str2[] = "exit";*/
	/*char *argv[100] = {"/bin/", NULL}, *argv2[100] = {"/usr/bin/", NULL};*/

	loc_t pathfinder[] = {
		{{"/usr/local/sbin/", NULL}},
		{{"/usr/local/bin/", NULL}},
		{{"/usr/sbin/", NULL}},
		{{"/usr/bin/", NULL}},
		{{"/sbin/", NULL}},
		{{"/bin/", NULL}},
		{NULL},
	};
	
	ssize_t bufsize = 1024, readcount = 0;
	char *buffer = NULL;
	int i = 0;
	buffer = malloc(bufsize * sizeof(char));
	if (!buffer)
	{
		printf("No mem, error 97\n");
		exit (97);
	}
	readcount = getline(&buffer, &bufsize, stdin);
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
	
	while (pathfinder[pos].path && stat(pathfinder[pos].path, buffer))
		pos++;
	if (pathfinder[pos].path)
		pathname = pathfinder[pos].path;
	strcat(pathname, buffer);
	if(!stat(pathname, &stats))
	{
		if (fork() == 0)
			execve(pathname, pathfinder[pos].path, NULL);
		wait(NULL);
		return (1);
	}
	else
		if(strcmp(buffer, str2))
			printf("COMMAND NOT FOUND\n");
		else
			exit (99);
	return (0);
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
