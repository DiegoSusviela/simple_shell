#include "header.h"

list_t *paths;
char *wopa;
int wopa2;

/**
 * start_new_prompt - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void start_new_prompt(void)
{
	static int first_time = 1;
	const char *CLEAR_SCREEN_ANSI;

	if (first_time)
	{
		CLEAR_SCREEN_ANSI = " \033[1;1H\033[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 0;
	}
}

/**
 * find_and_run_command - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

int find_and_run_command(void)
{
	int *index, pos1 = 0, flag3 = 0;
	char **argv, ***arg_aux, *buffer, str1[] = "exit";

	buffer = take_input(paths);
	if (!safty_nets(buffer, "x", buffer))
		return (0);
	if (buffer[0] == '\0')
		return (!safty_nets(NULL, "x", buffer));
	index = space_remover(buffer);
	if (!index)
		return (safty_nets(NULL, "xi", buffer, index));
	if (buffer[0] == '\0' && !index[0])
		return (!safty_nets(NULL, "xi", buffer, index));
	argv = ar(buffer, index);
	if (!argv)
		return (safty_nets(NULL, "ix", index, buffer));
	safty_nets(NULL, "ix", index, buffer);

	arg_aux = separator(argv);
	if (!arg_aux)
	{
		_puts("syntax error");
		_putchar('\n');
	}
	else
		while (arg_aux[pos1])
		{
			if (!_strcmp(arg_aux[pos1][0], str1))
				flag3 = 1;
			if (!check_builtins(pos1, flag3, arg_aux))
				if (!check_paths(arg_aux[pos1]))
					return (2);
			pos1++;
		}
	free(arg_aux);
	return (1);
}

/**
 * start_shell - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

void start_shell(void)
{
	if (isatty(STDIN_FILENO))
	{
		start_new_prompt();
		_puts("A sh*t here we go again -> ");
	}
	find_and_run_command();
	start_shell();
}

/**
 * main - Entry point
 *
 * Description: Show a message blablabla
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
	wopa = argv[0];
	wopa2 = argc;
	paths = create_paths();
	if (!paths)
	{
		perror("No mem to start shell");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	start_shell();
	return (0);
}
