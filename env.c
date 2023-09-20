#include "shell.h"

/**
 * _env - prints the environment string to stdout
 *
 * Return: 0
 */
void _env(void)
{
	int x = 0;
	char **env = environ;

	while (env[x])
	{
		size_t len = _strlen(env[x]);

		write(STDOUT_FILENO, env[x], len);
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
}

