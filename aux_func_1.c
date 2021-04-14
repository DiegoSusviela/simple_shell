#include "header.h"

extern list_t *paths;

int largo(int *index)
{
	int ret = 1, pos = 1;
	while(index[pos])
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

 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
