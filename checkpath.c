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
		if (output != NULL)
		{
			return (output);
		}
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
	char *buf;
	size_t i = _strlen(path);
	size_t j = _strlen(command);

	if (j == 0 && i > 0 && path[i - 1] == '/')
	{
		return (NULL);
	}

	buf = malloc(sizeof(char) * (i + j + 2));
	if (!buf)
	{
		return (NULL);
	}

	_strcpy(buf, path);
	if (i > 0 && path[i - 1] != '/')
	{
		_strcat(buf, "/");
	}
	_strcat(buf, command);

	return (buf);
}
/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, const char *src)
{
    char *dest_ptr = dest;

    while (*src)
    {
        *dest_ptr = *src;
        dest_ptr++;
        src++;
    }

    *dest_ptr = '\0';

    return dest;
}
