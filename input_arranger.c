#include "header.h"

extern list_t *paths;

/**
 * take_input - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

char *take_input(void)
{
	char *buffer = malloc(sizeof(char) * BUFFSIZE + 1);
	ssize_t readcount = 0;
	int i = 0;

	readcount = read(isatty(STDIN_FILENO), buffer, BUFFSIZE);

	if (!buffer)
		return (NULL);
	if (readcount <= 0)
	{
		free(buffer);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		safty_nets(NULL, "p", paths);
		exit(0);
	}
	if (buffer[readcount - 1] == '\n' || buffer[readcount - 1] == '\t')
		buffer[readcount - 1] = '\0';
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			buffer[i] = ';';
		if (buffer[0] == '#' || (buffer[i] == '#' && buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
	return (buffer);
}

/**
 * space_remover - Entry point
 * @to_remove: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */


int *space_remover(char *to_remove)
{
	int pos_rem = 0, pos_cont = 0, *index;

	index = malloc(sizeof(int) * BUFFSIZE);
	if (!index)
		return (NULL);
	while (to_remove[pos_rem] == ' ')
	{
		to_remove[pos_rem] = '\0';
		pos_rem++;
	}
	while (to_remove[pos_rem])
	{
		index[pos_cont] = pos_rem;
		if (to_remove[pos_rem] != ';')
		{
			while (to_remove[pos_rem] !=  ' ' && to_remove[pos_rem] != ';' && to_remove[pos_rem])
				pos_rem++;
			if (to_remove[pos_rem] == ';')
			{
				pos_cont++;
				index[pos_cont] = pos_rem;
				to_remove[pos_rem] = '\0';
			}
		}
		else
		{
			to_remove[pos_rem] = '\0';
			pos_rem++;
		}
		while (to_remove[pos_rem] == ' ')
		{
			to_remove[pos_rem] = '\0';
			pos_rem++;
		}
		pos_cont++;
	}
	index[pos_cont] = 0;
	return (index);
}

/**
 * separator - Entry point
 * @argv: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

char ***separator(char **argv)
{
	int pos = 0, pos1 = 0, pos2 = 0;
	char str1[] = ";", str2[] = {'\n','\0'};
	char ***arg_aux;
	char **sub_argv;

	if (!_strcmp(argv[0], str1))
		return (NULL);

	arg_aux = malloc(sizeof(char ***) * 150);
	sub_argv = malloc(sizeof(char **) * 250);

	pos = 0;
	while (argv[pos])
	{
		if (_strcmp(argv[pos], str1) && _strcmp(argv[pos], str2))
		{
			sub_argv[pos2] = _strdup(argv[pos]);
			pos2++;
		}
		else
		{
			sub_argv[pos2] = NULL;
			arg_aux[pos1] = sub_argv;
			if (argv[pos + 1])
				sub_argv = malloc(sizeof(char **) * 250);
			pos1++;
			pos2 = 0;
		}
		pos++;
	}
	sub_argv[pos2] = NULL;
	arg_aux[pos1] = sub_argv;
	arg_aux[pos1 + 1] = NULL;
	safty_nets(NULL, "a", argv);
	return (arg_aux);
}

/**
 * ar - Entry point
 * @buffer: wopa
 * @index: ea
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

char **ar(char *buffer, int *index)
{
	char **argv;
	int cont = 0, iter;

	argv = malloc(sizeof(char *) * (largo(index) + 1));
	if (!argv)
		return (NULL);
	for (cont = 0; cont < largo(index); cont++)
	{
		argv[cont] = malloc(sizeof(char) * BUFFSIZE);
		if (!argv[cont])
		{
			while (cont >= 0)
			{
				free(argv[cont]);
				cont--;
			}
			return (NULL);
		}
		iter = 0;
		while (buffer[index[cont] + iter])
		{
			argv[cont][iter] = buffer[index[cont] + iter];
			iter++;
		}
		if (!iter)
		{
			argv[cont][iter] = ';';
			argv[cont][iter + 1] = '\0';
		}
		else
			argv[cont][iter] = buffer[index[cont] + iter];
	}
	argv[cont] = NULL;
	return (argv);
}
