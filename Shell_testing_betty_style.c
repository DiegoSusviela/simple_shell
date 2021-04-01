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

	printf ("$ ");
	scanf("%s", str);
	strcat(command, str);
	strcat(command2, str);
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
				execve(command, argv, NULL);
			wait(NULL);
		}
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
