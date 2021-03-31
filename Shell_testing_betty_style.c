#include "header.h"
#include <limits.h>

/*
* main: this is a test for shell
*
*Return: 1 in success
*/
/*
void shell(void)
{
	char str[200], str1[] = "ls", str2[] = "exit";
	char current_path[PATH_MAX];
	getcwd(current_path, sizeof(current_path));
	char *envp[] = {"PATH=/bin", 0};
	char *argv[100] = {"/bin/ls", current_path, NULL};


	printf ("$ ");
	scanf("%s", str);
	printf("Current working dir: %s\n", current_path);
	if (!strcmp(str, str1))
	{
		if (fork() == 0)
			execve(argv[0], argv, NULL);	
	}
	else
		if(strcmp(str, str2))
			printf("unknown command\n");
		else
			exit (99);
	shell();
}
*/
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
			int p_ppid = getppid();
			printf("%i\n", p_ppid);
			if (fork() == 0)
			{
				int p_pid = getpid();
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
}
int main(void)
{
	shell();
	return (1);
}
