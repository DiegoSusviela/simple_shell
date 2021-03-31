#include "header.h"
#include <limits.h>

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void shell(void)
{
	char str[200], str1[] = "ls", str2[] = "exit";
	char current_path[PATH_MAX];
	getcwd(current_path, sizeof(current_path));
	char *envp[] = {"PATH=/bin", 0};
	char *argv[] = {"ls", "-l", current_path, NULL};


	printf ("$ ");
	scanf("%s", str);
	printf("\n");
	printf("Current working dir: %s\n", current_path);
	if (!strcmp(str, str1))
		execve(argv[0], argv, envp);
	else
		if(strcmp(str, str2))
			printf("unknown command\n");
		else
			exit (99);
	shell();
}

int main(void)
{
	shell();
	return (1);
}
