#include "shell.h"

/**
* exitt - handles the exit command
* @command: tokenized command
* @line: input read from stdin
*
* Return: no return
*/
void exitt(char **command, char *line)
{
	free(line);
	freebuff(command);
	exit(0);
}

