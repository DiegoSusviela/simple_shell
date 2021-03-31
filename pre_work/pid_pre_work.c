#include "header.h"

int main(void)
{
	int p_pid, p_id;


	p_id = getpid();
	p_pid = getppid();
	printf("Process ID: %d\n", p_id);
	printf("Parent process ID: %d\n", p_pid);
	return (0);
}
