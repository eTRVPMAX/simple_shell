#include "shell.h"
#include <signal.h>

/**
 * execute_command - executes the given command
 * @command: the command to be executed
 * @environ: the environment variables
 * @av: the argument vector
 */
void execute_command(char **command, char **environ, char **av)
{
	char *path = NULL;
	char **paths = NULL;
	char *pathcommand = NULL;

	path = path_handler();
	paths = tokenize(path);
	pathcommand = checkpath(paths, command[0]);

	if (!pathcommand)
	{
		perror(av[0]);
	}
	else
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
				exit(98);
			}
			break;
		default:
			wait(NULL);
			break;
		}
	}
}

/**
 * main - carries out the read, execute then print output loop
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment vector
 *
 * Return: 0
 */
int main(int argc, char **argv, char *envp[])
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL;

	(void)envp, (void)argv;

	if (argc < 1)
		return (-1);
	signal(SIGINT, signal_handler);
	while (1)
	{
		freebuff(command);
		free(line);
		prompt();
		linesize = getline(&line, &bufsize, stdin);

		if (linesize < 0)
			break;
		info.count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		command = tokenize(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (checkbuiltin(command, line))
			continue;
		execute_command(command, environ, argv);
	}

	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}

