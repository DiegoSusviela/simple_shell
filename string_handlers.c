#include "header.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination parameter
 * @src: source parameter
 *
 * Return: a pointer to the resulting string dest
 *
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j;
	if (dest)
		for (i = 0; dest[i] != '\0'; i++)
		;
	if (src)
	{
		for (j = 0; src[j] != '\0'; j++)
			dest[i + j] = src[j];
		dest[i + j] = '\0';
	}
	return (dest);
}

/**
 * _strdup - Duplicates a string in a new space in memory
 * @str: parameter
 *
 * Return: a pointer to a newly alloc space in memory, containing a copy of str
 *
 */

char *_strdup(char *str)
{
	int i;
	char *p;

	if (str == NULL)
		return (NULL);
	p = malloc(sizeof(char) * BUFFSIZE);
	if (p == NULL)
		return (NULL);
	for (i = 0 ; i < (_strlen(str) + 1) ; i++)
	{
		p[i] = str[i];
	}
	return (p);
}

/**
 * _strcmp - compares two strings
 * @s1: destination parameter
 * @s2: source parameter
 *
 * Return: a pointer to the resulting string dest
 *
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - compares two strings with one delimiter
 * @str1: destination parameter
 * @str2: source parameter
 * @n: delimiter
 *
 * Return: a pointer to the resulting string dest
 *
 */

int _strncmp(const char *str1, const char *str2, int n)
{
	int i = 0;

	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			break;
		i++;
	}
	if (i == n)
		return (0);
	return (1);
}

/**
 * _atoi - convert a string to an integer
 * @s: parameter of pointer s
 *
 * Description: convert a string to an integer
 *
 * Return: num * sign
 */

int _atoi(char *s)
{
	int flag = 1;
	unsigned int num = 0;

	do {
		if (*s == '-')
			flag *= -1;

		else if (*s >= '0' && *s <= '9')
			num = (num * 10) + (*s - '0');

		else if (num > 0)
			break;
	} while (*s++);

	return (num * flag);
}
