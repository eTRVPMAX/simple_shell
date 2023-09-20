#include "shell.h"

/**
 * checkbuiltin - checks whether the command is a built-in function
 * or an executable
 * @cmd: tokenized user input
 * @buf: line derived from the getline function
 *
 * Return: 1 if the command is executed, 0 if the command is not executed
 */

int checkbuiltin(char **cmd, char *buf)
{
	char firstChar = **cmd;

	if (handle_builtin(cmd, buf))
		return (1);
	if (firstChar == '/')
	{
		execute(cmd[0], cmd);
		return (1);
	}
	return (0);
}

