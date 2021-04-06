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


char *_strcpy(char *dest, char *src)
{
	int index = 0;

	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';

	return (dest);
}

 void _puts(char *str)
 {
	 int index = 0;

	 while (str[index])
	 {
		 _putchar(str[index]);
		 index++;
	 }
	 _putchar('\n');
 }



/*
	if (amount_of_words > 1)
	{
		start = 1;
		pos_dir = 0;
		am_dir = 0;
		for (iter = 1; iter < amount_of_words; iter++)
		{
			count = 0;
			pos_dir = 0;
	
			if (buffer[index[iter]] == '-' && buffer[index[iter] + 1])
			{
				if (flag == 0)
				{
					flag = 1;
					arguments[0] = '-';
				}
				count++;
				while (buffer[index[iter] + count])
				{
					arguments[start] = buffer[index[iter] + count];
					start++;
					count++;
				}
				arguments[start] = '\0';
			}
			else
			{
				while (buffer[index[iter] + count])
				{
					directorios[am_dir][pos_dir] = buffer[index[iter] + count];
					pos_dir++;
					count++;
				}
				directorios[am_dir][pos_dir] = '\0';
				am_dir++;
			}				
		}
	}*/

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
