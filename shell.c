#include "shell.h"
#include <signal.h>

/**
 * read_input - reads input from stdin
 * @line: pointer to the input line
 * @bufsize: pointer to the buffer size
 * @command: pointer to the command array
 * @paths: pointer to the paths array
 * @pathcommand: pointer to the path command
 *
 * Return: number of characters read, or -1 on failure
 */
ssize_t read_input(char **line, size_t *bufsize,
char ***command, char ***paths,
char **pathcommand)
{
	ssize_t linesize;

	prompt();
	linesize = getline(line, bufsize, stdin);
	if (linesize < 0)
		return (-1);
	info.count++;
	if ((*line)[linesize - 1] == '\n')
		(*line)[linesize - 1] = '\0';
	*command = tokenize(*line);
	if (*command == NULL || **command == NULL || ***command == '\0')
		return (linesize);
	*paths = tokenize(path_handler());
	*pathcommand = checkpath(*paths, (*command)[0]);
	return (linesize);
}

/**
 * execute_command - executes the command using fork and execve
 * @line: the input line
 * @pathcommand: the path command to execute
 * @command: the command array
 * @av: argument vector
 *
 * Return: void
 */
void execute_command(char *line, char *pathcommand, char **command, char **av)
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

/**
 * main - carries out the read, execute then print output loop
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
		freebuff(command);
		freebuff(paths);
		free(pathcommand);
		linesize = read_input(&line, &bufsize, &command, &paths, &pathcommand);
		if (linesize < 0)
			break;
		if (!pathcommand)
		{
			perror(av[0]);
		}
		else
		{
			execute_command(line, pathcommand, command, av);
		}
	}
	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}
