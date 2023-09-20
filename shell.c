#include "shell.h"
#include <signal.h>

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

    path = path_handler();
    paths = tokenize(path);

    while (1)
    {
        freebuff(command);
        free(pathcommand);
        prompt();
        linesize = getline(&line, &bufsize, stdin);
        if (linesize < 0)
            break;
        info.count++;
        if (line[linesize - 1] == '\n')
            line[linesize - 1] = '\0';
        command = tokenize(line);
        if (!command || !(*command) || !(**command))
            continue;
        if (checkbuiltin(command, line))
            continue;
        pathcommand = checkpath(paths, command[0]);
        if (!pathcommand)
            perror(av[0]);
        else
            execute(pathcommand, command);
    }

    freebuff(command);
    freebuff(paths);
    free(line);
    return (0);
}
