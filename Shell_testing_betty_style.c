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
		CLEAR_SCREEN_ANSI = "\e[1;1H[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 1;
	}
	printf("$");
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

	printf ("$ ");
	scanf("%s", str);
	strcat(command, str);
	/*printf("Current working dir: %s\n", current_path);*/
	if(!stat(command, &stats))
	{
		int p_ppid = getpid();
		printf("%i\n", p_ppid);
		if (fork() == 0)
		{
			int p_pid = getppid();
			printf("%i\n", p_pid);
			execve(command, argv, NULL);
		}
		wait(NULL);
	}
	else
		if(strcmp(str, str2))
			printf("COMMAND NOT FOUND\n");
		else
			exit (99);
	shell();
}

/*
void shell(void)
{
	char str[200], str1[] = "ls", str2[] = "exit";
	char current_path[PATH_MAX];
	getcwd(current_path, sizeof(current_path));
	char *envp[] = {"PATH=/bin", 0};
	char *argv[100] = {"/bin/ls", current_path, NULL};

	while (1)
	{
		printf ("$ ");
		scanf("%s", str);
		printf("Current working dir: %s\n", current_path);
		if (!strcmp(str, str1))
		{
			int p_ppid = getpid();
			printf("%i\n", p_ppid);
			if (fork() == 0)
			{
				int p_pid = getppid();
				printf("%i\n", p_pid);
				execve(argv[0], argv, NULL);
			}
			else
				wait(NULL);
		}
		else
			if(strcmp(str, str2))
				printf("unknown command\n");
			else
				exit (99);
	}
}*/
int main(void)
{
	type_prompt();
	shell();
	return (1);
}
