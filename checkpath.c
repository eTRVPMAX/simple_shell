#include "shell.h"

/**
 * checkpath - checks whether path is valid
 * @path: tokenized path
 * @command: user entered command
 *
 * Return: path appended with command on success, NULL on failure
 */
char *checkpath(char **path, char *command)
{
	int i = 0;
	char *output;

	while (path[i])
	{
		output = addpath(path[i], command);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	return (NULL);
}

/**
 * addpath - adds path to command
 * @path: path of command
 * @command: user entered command
 *
 * Return: buffer containing command with path on success, NULL on failure
 */
char *addpath(char *path, char *command)
{
	int i = 0, j = 0;
	int pathlen = 0;
	int commandlen = 0;
	char *buf = malloc(sizeof(char) * (pathlen + commandlen + 2));

	if (command == NULL)
		command = "";
	if (path == NULL)
		path = "";
	while (path[pathlen] != '\0')
		pathlen++;
	while (command[commandlen] != '\0')
		commandlen++;
	if (!buf)
		return (NULL);
	for (i = 0; i < pathlen; i++)
		buf[i] = path[i];
	buf[i++] = '/';

	for (j = 0; j < commandlen; j++)
		buf[i + j] = command[j];

	buf[i + j] = '\0';

	return (buf);
}
