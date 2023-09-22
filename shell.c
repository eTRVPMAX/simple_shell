#include "shell.h"
#include <signal.h>

/**
 * commenthandler - Removes comments from the input string.
 * The comments are denoted by '#' character.
 *
 * @input: - The input string.
 */
void commenthandler(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}

/**
 * freeit - Frees the memory allocated for the command array,
 * paths array, and pathcommand string.
 * @command: The command array to free.
 * @paths: The paths array to free.
 * @pathcommand: The pathcommand string to free.
 */
void freeit(char **command, char **paths, char *pathcommand)
{
	freebuff(command);
	freebuff(paths);
	free(pathcommand);
}

/**
 * main - carries out the read, execute, then print output loop
 * @ac: argument count
 * @av: argument vector
 * @envp: environment vector
 *
 * Return: 0
 */
int main(int ac, char **av, char *envp[])
{
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;
	(void)envp, (void)av;
	if (ac < 1)
		return (-1);
	signal(SIGINT, signal_handler);
	while (1)
	{
		freeit;
		prompt();
		linesize = getline(&line, &bufsize, stdin);
		if (linesize < 0)
			break;
		info.count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		commenthandler(line);
		if (line[0] == '\0')
			continue;
		command = tokenize(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (checkbuiltin(command, line))
			continue;
		path = path_handler();
		paths = tokenize(path);
		pathcommand = checkpath(paths, command[0]);
		if (!pathcommand)
			perror(av[0]);
		else
			executecommand(pathcommand, command, av, line);
	}
	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}

/**
 * executecommand - executes a command
 * @pathcommand: the path of the command to execute
 * @command: an array of strings representing the command and its arguments
 * @av: the argument vector
 * @line: the input line
 */
void executecommand(char *pathcommand, char **command, char **av, char *line)
{
	switch (fork())
	{
		case -1:
			perror(av[0]);
			break;
		case 0:
			if (execve(pathcommand, command, environ) == -1)
			{
				perror(av[0]);
				freebuff(command);
				free(line);
				exit(98);
			}
			break;
		default:
			wait(NULL);
			break;
	}
}
