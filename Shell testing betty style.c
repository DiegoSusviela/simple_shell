#include "header.h"

/*
* main: this is a test for shell
*
*Return: 1 in success
*/

int main(void)
{
	char *str;

	printf ("$ ");
	scanf("%s", str);
	printf("\n");

	if (str == 'ls')
		printf("folder empty\n");
	else
		printf("unknown command\n");
	return (1);
}
