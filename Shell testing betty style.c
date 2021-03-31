#include "header.h"

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void shell(void)
{
	char str[200], str1[] = "ls", str2[] = "exit";

	printf ("$ ");
	scanf("%s", str);
	printf("\n");

	if (!strcmp(str, str1))
		printf("folder empty\n");
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
