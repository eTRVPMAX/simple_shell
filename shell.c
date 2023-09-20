#include "shell.h"
#include <signal.h>

void handlecommands(char **paths, char *av0) {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t linesize = 0;
    char **command = NULL;
    char *pathcommand = NULL;
    
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
        if (!command || !(*command) || !(**command))
            continue;
        if (checkbuiltin(command, line))
            continue;
        pathcommand = checkpath(paths, command[0]);
        if (!pathcommand)
            perror(av0);
        else
            execute(pathcommand, command);
    }

    if (linesize < 0 && flags.interactive)
        write(STDERR_FILENO, "\n", 1);

    freebuff(command);
    free(line);
}

int main(int ac, char **av, char *envp[])
{
    char *path = NULL;
    char **paths = NULL;

    (void)envp, (void)av;

    if (ac < 1)
        return (-1);

    signal(SIGINT, signal_handler);

    path = path_handler();
    paths = tokenize(path);

    handlecommands(paths, av[0]);

    freebuff(paths);
    free(path);
    return (0);
}
