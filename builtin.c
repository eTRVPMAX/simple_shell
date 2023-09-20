#include "shell.h"

/**
* handle_builtin - handles execution of builtin functions
* @command: tokenized commands
* @line: input read from stdin
* struct builtin - struct holds the names of builtin functions
* Return: 1 if executed, 0 if not
*/
int handle_builtin(char **command, char *line)
{
	struct builtin builtin = {"env", "exit"};

	if (_strcmp(*command, builtin.env) == 0)
	{
		_env();
		return (1);
	}
	else if (_strcmp(*command, builtin.exit) == 0)
	{
		exitt(command, line);
		return (1);
	}
	return (0);
}

