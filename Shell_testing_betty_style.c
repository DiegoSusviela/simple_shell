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
		CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 1;
	}
}

char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0;
	printf("%s\n", environ[i]);
	while(environ[i]) 
		if (!strcmp(environ[i], name))
			return (environ[i]);
		else
			i++;
	return (NULL);
}

void shell(void)
{
	char str[200], str1[] = "ls", str2[] = "exit";
	char current_path[PATH_MAX];
	getcwd(current_path, sizeof(current_path));
	char *envp[] = {"PATH=/bin", 0};
	char *argv[100] = {"/bin/", NULL};
	struct stat stats;
	char command[] = "/bin/";
	char command2[] = "/usr/bin/";
	char *argv2[100] = {"/usr/bin/", NULL};

	printf ("$ ");
	scanf("%s", str);
	strcat(command, str);
	strcat(command2, str);
	if (_getenv(str))
		printf("%s\n", _getenv(str));
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
			extern char **environ;
			int i = 0;

			while(environ[i]) 
				printf("%s\n", environ[i++]); 
/*
			if (fork() == 0)
				execve(command2, argv2, NULL);
			wait(NULL);
		*/}
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
