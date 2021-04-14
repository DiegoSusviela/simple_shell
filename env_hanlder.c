
#include "header.h"

extern list_t *paths;


/**
 * _getenv - Entry point
 * @name: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

char *_getenv(const char *name)
{
	int i, cont = 0, pos = 0;
	size_t j;
	char *path;
	extern char **environ;

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j++;
			while (environ[i][j + cont])
				cont++;
			path = malloc(sizeof(char) * (cont + 1));
			if (!path)
				return (NULL);
			while (environ[i][j])
			{
				path[pos] = environ[i][j];
				pos++;
				j++;
			}
			path[pos] = '\0';
			return (path);
		}
	}
	return (NULL);
}

/**
 * print_env - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void print_env(void)
{
	int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
		_puts(environ[i]);
}

/**
 * update_old_pwd - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void update_old_pwd(void)
{
	int i, pos2 = 0;
	size_t j;
	char *name = "OLDPWD=";
	char current_path[PATH_MAX];
	extern char **environ;

	getcwd(current_path, sizeof(current_path + 1));

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j = 0;
			while (name[pos2])
			{
				environ[i][j] = name[pos2];
				pos2++, j++;
			}
			pos2 = 0;
			while (current_path[pos2])
			{
				environ[i][j] = current_path[pos2];
				j++, pos2++;
			}
			environ[i][j] = '\0';
		}
	}
}

/**
 * update_pwd - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void update_pwd(void)
{
	int i, pos2 = 0;
	size_t j;
	char *name = "PWD=";
	char current_path[PATH_MAX];
	extern char **environ;

	getcwd(current_path, sizeof(current_path + 1));

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j = 0;
			while (name[pos2])
			{
				environ[i][j] = name[pos2];
				pos2++, j++;
			}
			pos2 = 0;
			while (current_path[pos2])
			{
				environ[i][j] = current_path[pos2];
				j++, pos2++;
			}
			environ[i][j] = '\0';
		}
	}
}
