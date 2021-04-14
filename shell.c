#include "header.h"

list_t *paths;

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

int find_and_run_command()
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
		write(1, "syntax error\n", 13);
	else
		while (arg_aux[pos1])
		{
			if (!strcmp(arg_aux[pos1][0], str1))
				flag3 = 1;
			if (!check_builtins(pos1, flag3, arg_aux))
				check_paths(arg_aux[pos1]);
			pos1++;
		}
	free(arg_aux);
	return (1);
}

void start_shell()
{
	if (isatty(STDIN_FILENO))
	{
		start_new_prompt();
		write(1, "(. Y .) ", 8);
	}
	fflush(NULL);
	find_and_run_command(paths);
	start_shell(paths);
}

int main()
{
	paths = create_paths();
	if (!paths)
	{
		perror("No mem to start shell");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	start_shell(paths);
	return (1);
}
