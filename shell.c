#include "shell.h"
#include <signal.h>

/**
* main - carries out the read, execute then print output loop
* @argc: argument count
* @argv: argument vector
* @envv: environment vector
*
* Return: 0
*/
int main(int argc, char **argv, char *envv[])
{
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;
	(void)envv, (void)argv;
	if (argc < 1)
		return (-1);
	signal(SIGINT, signal_handler);
	while (1)
	{
		prompt();
		linesize = getline(&line, &bufsize, stdin);
		if (linesize < 0)
			break;
		info.count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		command = tokenize(line);
		if (command == NULL || *command == NULL || **command == '\0') continue;
		if (checkbuiltin(command, line)) continue;
		path = path_handler();
		paths = tokenize(path);
		pathcommand = checkpath(paths, command[0]);
		if (!pathcommand) 
		{
			perror(argv[0]);
		}
		else
		{
			switch (fork())
			{
				case -1:
					perror(argv[0]);
					break;
				case 0:
					if (execve(pathcommand, command, environ) == -1)
					{
						perror(argv[0]);
						exit(98);
					}
					break;
				default:
					wait(NULL);
					break;
			}
			free(pathcommand);
		}
		freebuff(command);
		freebuff(paths);
		free(path);
	}
	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);
	free(line);
	return (0);
}
