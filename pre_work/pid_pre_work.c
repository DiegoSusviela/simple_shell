#include "header.h"

int main(void)
{
	int p_pid;

	p_pid = getppid();
	printf("Parent process ID: %d\n", p_pid);
	return (0);
}
