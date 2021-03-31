#include "header.h"

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void shell(void)
{
	char str[200], str1[] = "/bin/ls", str2[] = "exit";
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf ("$ ");
	scanf("%s", str);
	printf("\n");

	if (!strcmp(str, str1))
		execve(argv[0], argv, NULL);
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
