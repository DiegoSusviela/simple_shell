#include "header.h"

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

void main(void)
{
	char *str;

	printf ("$ ");
	scanf("%s", str);
	printf("\n");

	if (str == "ls")
		printf("folder empty");
	else
		printf("unknown command");
	return (1);
}
