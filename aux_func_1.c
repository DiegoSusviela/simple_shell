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
	char *dest;
	unsigned int contador, max_size = new_size;
	char *old_ptr = ptr;

	if (!ptr)
	{
		dest = malloc(new_size);
		return (dest);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	dest = malloc(new_size);
	if (!dest)
		return (NULL);
	if (new_size > old_size)
		max_size = old_size;
	for (contador = 0; contador < (max_size - 1); contador++)
		dest[contador] = old_ptr[contador];
	free(ptr);
	return (dest);
}