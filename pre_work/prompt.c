#include "header.h"


int main(void)
{
	char *buffer;
	size_t str1;

    buffer = (char *)malloc(BUFSIZE * sizeof(char));

	printf("$ ");
	str1 = getline(&buffer,BUFSIZE,stdin);
	printf("\n");
	printf("%s", str1);
	printf("\n");
	free(buffer);

	return (strlen(str1));
}
