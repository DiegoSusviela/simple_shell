#include "header.h"

/**
 * largo - Entry point
 * @index: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

int largo(int *index)
{
	int ret = 1, pos = 1;

	while (index[pos])
	{
		ret++;
		pos++;
	}
	return (ret);
}

/**
 * _puts - Entry point
 * @str: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void _puts(char *str)
{
	int marker = 0;

	while (*(str + marker))
	{
		_putchar(*(str + marker));
		marker++;
	}
	_putchar('\n');
}

/**
 *	_putchar - Entry point
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _realloc - Entry point
 * @ptr: parameter
 * @old_size: parameter
 * @new_size: parameter
 *
 * Description: function that creates an array of integers
 *
 * Return: the pointer to the newly created space in memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	unsigned int i;
	char *PTR = ptr;

	if (!PTR)
	{
		new = malloc(new_size);
		if (new == NULL)
			return (NULL);
		return (new);
	}
	if (new_size == old_size)
		return (PTR);
	if (new_size == 0 && PTR != NULL)
	{
		free(PTR);
		return (NULL);
	}
	if (new_size > old_size)
	{
		new = malloc(new_size);
		if (new == NULL)
			return (NULL);
		for (i = 0; i < old_size; i++)
			new[i] = PTR[i];
		free(PTR);
	}
	return (new);
}
