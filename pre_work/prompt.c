#include "header.h"


int main(void)
{
	char *buffer;
	size_t bufsize = 64;
	size_t str1;

    buffer = (char *)malloc(bufsize * sizeof(char));

	printf("$ ");
	str1 = getline(&buffer,&bufsize,stdin);
	printf("\n");
	printf("%s", buffer);
	printf("\n");
	free(buffer);

	return (str1);
}
