#include "header.h"

extern list_t *paths;

/**
 * check_builtins - Entry point
 * @pos1: wopa
 * @flag: wopa
 * @arg_aux: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

int check_builtins(int pos1, int flag, char ***arg_aux)
{
	int i = 0, iter = 0;
	char **argv;

	builtins_t built[] = {
		{"exit", salir},
		{"env", env},
		{"cd", cd},
		/**
		*{"setenv", setenv},
		*{"unsetenv", unsetenv},
		*/
		{NULL, NULL}
	};

	while (built[i].f)
	{
		if (!_strcmp(arg_aux[pos1][0], built[i].command))
			break;
		i++;
	}
	if (built[i].f)
	{
		if (flag)
		{
			argv = malloc(sizeof(char **) * BUFFSIZE);
			while (arg_aux[pos1][iter])
			{
				argv[iter] = _strdup(arg_aux[pos1][iter]);
				iter++;
			}
			argv[iter] = NULL;
			liberar_arg_aux(arg_aux, pos1);
			free(arg_aux);
		}
		else
			argv = arg_aux[pos1];
		built[i].f(argv);
		return (1);
	}
	return (0);
}

/**
 * salir - Entry point
 * @pos1: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void salir(char **argv)
{
	int ato;

	safty_nets(NULL, "p", paths);
	if (argv[1])
	{
		ato = _atoi(argv[1]);
		safty_nets(NULL, "a", argv);
		exit(ato);
	}
	safty_nets(NULL, "a", argv);
	exit(0);
}

/**
 * env - Entry point
 * @argv: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void env(char **argv)
{
	print_env();
	safty_nets(NULL, "a", argv);
}

/**
 * cd - Entry point
 * @argv: wopa
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void cd(char **argv)
{
	char *target, str5[] = "-";

	if (!argv[1])
		target = _getenv("HOME");
	else
		if (!_strcmp(argv[1], str5))
		{
			target = _getenv("OLDPWD");
			_puts(target);
		}
		else
			target = _strdup(argv[1]);
	update_old_pwd();
	chdir(target);
	update_pwd();
	safty_nets(NULL, "ax", argv, target);
}
