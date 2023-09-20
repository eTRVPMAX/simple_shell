#include "shell.h"

/**
* tokenize - creates tokens from given input
* @line: to be tokenized
*
* Return: array of strings
*/
char **tokenize(char *line)
{
	char *current = NULL, *buffpointer = NULL, *token = NULL, *delim = " :\t\r\n";
	char **tokens = NULL;
	int tokensize = 1;
	size_t index = 0, flag = 0;

	current = _strdup(line);
	if (!current)
		return (NULL);
	buffpointer = current;

	while (*buffpointer)
	{
		if (_strchr(delim, *buffpointer) != NULL && flag == 0)
		{
			tokensize++;
			flag = 1;
		}
		else if (_strchr(delim, *buffpointer) == NULL && flag == 1)
			flag = 0;
		buffpointer++;
	}
	tokens = malloc(sizeof(char *) * (tokensize + 1));
	token = strtok(current, delim);
	while (token)
	{
		tokens[index] = _strdup(token);
		if (tokens[index] == NULL)
		{
			free(tokens);
			return (NULL);
		}
		token = strtok(NULL, delim);
		index++;
	}
	tokens[index] = '\0';
	free(current);
	return (tokens);
}

