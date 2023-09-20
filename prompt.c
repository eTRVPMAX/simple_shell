#include "shell.h"

/**
* prompt - prints $ to let user know the program is
* ready to take their input
* prints the prompt if the shell is in interactive mode
* Return: no return
*/
void prompt(void)
{
	int _stdin = isatty(STDIN_FILENO);
	int _stdout = isatty(STDOUT_FILENO);

	if (_stdin == 1 && _stdout == 1)
		flags.interactive = 1;

	if (flags.interactive)
		write(STDERR_FILENO, "$ ", 2);
}

