#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

extern char **environ;
extern __sighandler_t signals(int __sig, __sighandler_t __handler);
int checkbuiltin(char **cmd, char *buf);
void prompt(void);
void signal_handler(int m);
char **tokenize(char *line);
int handle_builtin(char **command, char *line);
void exitt(char **command, char *line);
void _env(void);
char *checkpath(char **path, char *command);
char *addpath(char *path, char *command);
void freebuff(char **buf);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_strcat(char *dest, const char *src);
int _strlen(char *s);
char *_strdup(char *s);
int _strncmp(char *s1, char *s2, int n);
char *_strchr(char *s, char c);
void execute(char *cp, char **cmd);
char *path_handler(void);
char *_strcpy(char *dest, const char *src);
void handlecommands(char **paths, char *av0);
/**
 * struct builtin - struct stores information about built-in commands
 * @env: Environment variable
 * @exit: Flag to indicate if the program should exit
 */
struct builtin
{
	char *env;
	char *exit;
} builtin;

/**
 * struct info - struct stores the information
 * @exite: Flag to indicate if the program should exit
 * @count: Counter for keeping track of something
 */
struct info
{
	int exite;
	int count;
} info;

/**
* struct flags - struct stores the flags
* @interactive:  Flag to indicate if the program is running
* in interactive mode
*/
struct flags
{
	bool interactive;
} flags;

#endif

