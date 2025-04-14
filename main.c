/**

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

*
 * main - Entry point for simple shell that executes single-word commands
 * Return: Always 0 (Success)
 *
int main(void)
{
char *line = NULL, *cmd;
size_t len = 0;
ssize_t read;
pid_t pid;
char *argv[2];

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
exit(0);
}

if (line[read - 1] == '\n')
line[read - 1] = '\0';

cmd = line;
while (*cmd == ' ')
cmd++;

if (*cmd == '\0')
continue;

pid = fork();
if (pid == 0)
{
argv[0] = cmd;
argv[1] = NULL;

if (execve(argv[0], argv, environ) == -1)
perror("./hsh");

exit(1);
}
else if (pid > 0)
{
wait(NULL);
}
else
{
perror("fork");
}
}

free(line);
return (0);
}


TASK 3 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_ARGS 64

extern char **environ;

**
 * parse_line - splits line into tokens
 * @line: user input
 * Return: array of tokens (arguments), NULL terminated
 *
char **parse_line(char *line)
{
char **args = malloc(MAX_ARGS * sizeof(char *));
char *token;
int i = 0;

if (!args)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(line, " \t\n");
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " \t\n");
}
args[i] = NULL;
return (args);
}

**
 * main - Simple Shell 0.2 that handles command + arguments
 * Return: 0 on success
 *
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
char **args;
pid_t pid;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
exit(0);
}

if (line[0] == '\n')
continue;

args = parse_line(line);
if (!args[0])
{
free(args);
continue;
}

pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) == -1)
{
perror("./hsh");
exit(EXIT_FAILURE);
}
}
else if (pid > 0)
{
wait(NULL);
}
else
{
perror("fork");
}

free(args);
}
free(line);
return (0);
}
*/

/** TASK 4 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_ARGS 64

extern char **environ;

/**
 * _getenv - Get value of environment variable
 * @name: name of variable
 * Return: pointer to value or NULL
 */
char *_getenv(const char *name)
{
int i;
size_t len = strlen(name);

for (i = 0; environ[i]; i++)
{
if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
return (environ[i] + len + 1);
}
return (NULL);
}

/**
 * find_command_path - Search for executable in PATH
 * @command: command name
 * Return: full path or NULL
 */
char *find_command_path(char *command)
{
char *path_env, *path_copy, *token;
char full_path[1024];

if (strchr(command, '/'))
return (strdup(command));

path_env = _getenv("PATH");
if (!path_env)
return (NULL);

path_copy = strdup(path_env);
if (!path_copy)
return (NULL);

token = strtok(path_copy, ":");
while (token)
{
snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (strdup(full_path));
}
token = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}

/**
 * parse_line - Split user input into arguments
 * @line: raw input
 * Return: NULL-terminated array of arguments
 */
char **parse_line(char *line)
{
char **args = malloc(MAX_ARGS * sizeof(char *));
char *token;
int i = 0;

if (!args)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(line, " \t\n");
while (token && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " \t\n");
}
args[i] = NULL;
return (args);
}

/**
 * main - Simple shell 0.3
 * Return: 0
 */
int main(void)
{
char *line = NULL, *cmd_path;
size_t len = 0;
ssize_t read;
char **args;
pid_t pid;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

read = getline(&line, &len, stdin);
if (read == -1)
{
free(line);
exit(0);
}

if (line[0] == '\n')
continue;

args = parse_line(line);
if (!args[0])
{
free(args);
continue;
}

cmd_path = find_command_path(args[0]);
if (!cmd_path || access(cmd_path, X_OK) != 0)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
free(args);
free(cmd_path);
continue;
}

pid = fork();
if (pid == 0)
{
execve(cmd_path, args, environ);
perror("./hsh");
exit(EXIT_FAILURE);
}
else if (pid > 0)
{
wait(NULL);
}
else
{
perror("fork");
}

free(cmd_path);
free(args);
}

free(line);
return (0);
}

