#include "shell.h"

/**
 * execute - executes commands entered by users
 * @comandprompt: command
 * @cmd: vector array of pointers to commands
 * Return: 0
 */
void execute(char *comandprompt, char **cmd)
{
	pid_t pid;
	char **env = environ;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror(comandprompt);
		return;
	}
	if (pid == 0)
	{
		if (execve(comandprompt, cmd, env) == -1)
		{
			perror(comandprompt);
			free(comandprompt);
			freebuff(cmd);
			exit(98);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

