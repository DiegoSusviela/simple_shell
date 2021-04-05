#include "header.h"

int largo(int *index)
{
	int ret = 1, pos = 1;
	while(index[pos])
		ret++;
	return (ret);
}

int largo_palabra(char *aux)
{
	int pos = 0, ret = 0;

	while(aux[pos])
	{
		pos++;
		ret++;
	}
	return (ret);
}


char **argv(char *buffer, int *index)
{
	char **argv, *aux;
	int cont = 0, iter;


	argv = malloc(sizeof(char *) * largo(index));	

	for (cont = 0; cont < index; cont++)
	{
		aux = buffer[index[cont]];
		argv[cont] = malloc(sizeof(char) * largo_palabra(aux));
		iter = 0;
		while (buffer[index[cont] + iter])
		{
			argv[cont][iter] = buffer[index[cont] + iter];
			iter++;
		}
		argv[cont][iter] = NULL;
	}
	return (argv);
}



int main(void)
{
	char **argv;

    char *buffer;
    int *index;

    scanf("%s", buffer);
    scanf("%i", index);
    argv  = ar(buffer, index);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);

    return 0;
}
