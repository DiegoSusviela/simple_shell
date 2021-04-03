#include "header.h"
#include <limits.h>

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void type_prompt()
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

char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0;
	printf("%s\n", environ[i]);
	printf("%s\n", name);
	while(environ[i]) 
		if (!strcmp(environ[i], name))
			return (environ[i]);
		else
			i++;
	return (NULL);
}

void shell(void)
{
	char str[200], *str1, str2[] = "exit";
	/*char current_path[PATH_MAX];
	getcwd(current_path, sizeof(current_path));
	char *envp[] = {"PATH=/bin", 0};*/
	char *argv[100] = {"/bin/", NULL};
	struct stat stats;
	char command[] = "/bin/", command2[] = "/usr/bin/";
	char *argv2[100] = {"/usr/bin/", NULL};

	printf ("$ ");
	/*scanf("%s", str);*/



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



	/*strcpy(str1, str);*/
	strcat(command, str);
	strcat(command2, str);

	/*if (_getenv(str))
		printf("%s\n", _getenv(str));*/
	/*printf("Current working dir: %s\n", current_path);*/
	if(!stat(command, &stats))
	{
		if (fork() == 0)
			execve(command, argv, NULL);
		wait(NULL);
	}
	else
		if (!stat(command2, &stats))
		{
			if (fork() == 0)
				execve(command2, argv2, NULL);
			wait(NULL);
		}
		else
			if(strcmp(str, str2))
				printf("COMMAND NOT FOUND\n");
			else
				exit (99);
	shell();
}

int main(void)
{
	type_prompt();
	shell();
	return (1);
}
