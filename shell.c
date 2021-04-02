#include "header.h"
#include <limits.h>



void start_new_promtp(void)
{
	static int first_time = 1;
	const char *CLEAR_SCREEN_ANSI;

	if (first_time)
	{
		CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
		first_time = 0;
	}
}


char *take_user_input()
{
	int imput_lines;
	ssize_t bufsize = 0;
	char *input;

	if (getline(&input, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return (input);
} 

int validate_usr_in(char *usr_input)
{
	int pos = 0;

	while(usr_input[pos] && usr_input[pos] != ' ')
		pos++;
	if (usr_input[pos])
		return (0);
	return(1);
}

int find_and_run_command(char *use_input)
{
	return (0);
}
void start_shell(void)
{
	char *usr_input;

	printf("$ ");
	usr_input = take_user_input();
	if (validate_usr_in(usr_input))
	{
		printf("validacion correcta");
		if (!find_and_run_command(usr_input))
		{
			printf("Unkown command, error 98");
			free(usr_input);
			exit(98);
		}
	}
	else
	{
		printf("Invalid command, error 99");
		free(usr_input);
		exit(99);
	}
	start_shell();
}


int main()
{
	start_new_promtp();
	start_shell();
	return (1);
}