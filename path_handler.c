#include "shell.h"
#include <string.h>

/**
 * path_handler - finds the path from the global environment
 * Return: NULL if path is not found or path if path is found.
 */
char *path_handler(void)
{
	char **env = environ;
	char *path = NULL;

	while (*env != NULL)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = _strchr(*env, '=');
			if (path != NULL)
			{
				path++;
				return (path);
			}
		}
		env++;
	}
	return (NULL);
}

