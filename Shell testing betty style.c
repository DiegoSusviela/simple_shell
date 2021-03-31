#include "header.h"

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void shell(void)
{
	char str[200], str1[] = "ls";

	printf ("$ ");
	scanf("%s", str);
	printf("\n");

	if (strcmp(str, str1))
		printf("folder empty\n");
	else
		printf("unknown command\n");
	shell();
}

int main(void)
{
	shell();
	return (1);
}
