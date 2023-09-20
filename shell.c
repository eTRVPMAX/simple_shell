#include "shell.h"
#include <signal.h>

/**
 * main - carries out the read, execute, then print output loop
 * @ac: argument count
 * @av: argument vector
 * @envp: environment vector
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

    path = path_handler();
    paths = tokenize(path_handler());

    while (1)
    {
        freebuff(command);
        free(pathcommand);
        prompt();
        linesize = getline(&line, &bufsize, stdin);
        if (linesize < 0) break;
        info.count++;
        if (line[linesize - 1] == '\n') line[linesize - 1] = '\0';
        command = tokenize(line);
        if (!command || !(*command) || !(**command)) 
			continue;
        if (checkbuiltin(command, line)) 
			continue;
        pathcommand = checkpath(paths, command[0]);
        if (!pathcommand) perror(argv[0]);
        else execute(pathcommand, command);
    }
    if (linesize < 0 && flags.interactive) write(STDERR_FILENO, "\n", 1);
    freebuff(command);
    freebuff(paths);
    free(line);
    return (0);
}
