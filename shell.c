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
        if (command == NULL || *command == NULL || **command == '\0') continue;
        if (checkbuiltin(command, line)) continue;
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
                        free(line);
                        exit(98);
                    }
                    break;
                default:
                    wait(NULL);
                    break;
            }
        }
    }
    if (linesize < 0 && flags.interactive)
        write(STDERR_FILENO, "\n", 1);
    free(line);
    return (0);
}

