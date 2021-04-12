#include "header.h"

/**
 * _strlen - counts the length of a string
 * @s: string to check
 *
 * Description: Function that counts the amount of characters of a string
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int marker = 0;

	while (s[marker] != '\0')
		marker++;
	return (marker);
}
