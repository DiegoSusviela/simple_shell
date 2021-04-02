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
	ssize_t bufsize = 0;
	char *input = NULL;
	ssize_t readcount = 0;
	int i = 0;

	input = (char *)malloc(bufsize * sizeof(char));
	readcount = getline(&input, &bufsize, stdin);
	if (readcount == -1)
	{
		free(input);
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (input[readcount - 1] == '\n' || input[readcount - 1] == '\t')
		input[readcount - 1] = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '#' && input[i - 1] == ' ')
		{
			input[i] = '\0';
			break;
		}
		i++;
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

char *find_path(char *usr_input)
{
	/*char *test[] = "/bin/"; */
	return (0);
}

int find_and_run_command(char *usr_input)
{
	/*
	char *pathname;
	pathname = find_path(usr_input);
	*/
	struct stat stats;
	char pathname[] = "/bin/";
	char *argv[100] = {"/bin/", NULL};

	printf("%zi", strlen(usr_input));
	strcat(pathname, usr_input);
	printf("%s", pathname);
	printf("%zi", strlen(usr_input));
	if(!stat(pathname, &stats))
	{
		if (fork() == 0)
			execve(pathname, argv, NULL);
		wait(NULL);
		return (1);
	}
	return (0);
}

void start_shell(void)
{
	char *usr_input;

	printf("$ ");
	usr_input = take_user_input();
	if (validate_usr_in(usr_input))
	{
		printf("validacion correcta\n");
		if (!find_and_run_command(usr_input))
		{
			printf("Unkown command, error 98\n");
		}
	}
	else
	{
		printf("Invalid command, error 99\n");
	}
	free(usr_input);
	start_shell();
}


int main()
{
	start_new_promtp();
	start_shell();
	return (1);
}