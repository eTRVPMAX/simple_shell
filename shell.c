#include "shell.h"
#include <signal.h>

int main(int argc, char **argv, char *envp[])
{
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;

	(void)envp, (void)argv;

	if (argc < 1)
		return (-1);

	signal(SIGINT, signal_handler);

	while (1)
	{
		freebuff(command);
		freebuff(paths);
		free(pathcommand);
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

		switch (checkbuiltin(command, line))
		{
			case 1:
				continue;
			case 2:
				path = path_handler();
				paths = tokenize(path);
				pathcommand = checkpath(paths, command[0]);
				if (!pathcommand)
					perror(argv[0]);
				else
					execute(pathcommand, command);
				break;
			default:
				break;
		}
	}

	if (linesize < 0 && flags.interactive)
		write(STDERR_FILENO, "\n", 1);

	free(line);
	return (0);
}

