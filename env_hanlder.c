
#include "header.h"

extern list_t *paths;

char *_getenv(const char *name)
{
	extern char ** environ;
	int i, cont = 0, pos = 0;
	size_t j;
	char *path;

	for (i = 0; environ[i] != '\0'; i++)
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
		}
		if (!_strncmp(environ[i], name, j))
		{
			j++;
			while(environ[i][j + cont])
				cont++;
			path = malloc(sizeof(char) * (cont + 1));
			if (!path)
				return (NULL);
			while(environ[i][j])
			{
				path[pos] = environ[i][j];
				pos++;
				j++;
			}
			path[pos] = '\0';
			return(path);
		}
	}
	return (NULL);
}

void print_env()
{
	int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
		_puts(environ[i]);
}

void update_old_pwd()
{
	extern char ** environ;
	int i, pos2 = 0;
	size_t j;
	char *name = "OLDPWD=";
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));

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
void update_pwd()
{
	extern char ** environ;
	int i, pos2 = 0;
	size_t j;
	char *name = "PWD=";
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));

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
