#include "shell.h"

/**
 *signal_handler - it keeps track is interactive mode
 *@n: the signal number
 *Return: nothing
 */

void signal_handler(int n)
{
	(void)n;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "#cisfun$ ", 9);
}

