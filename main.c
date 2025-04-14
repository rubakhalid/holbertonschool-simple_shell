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

*/


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
 * parse_line - splits line into tokens
 * @line: user input
 * Return: array of tokens (arguments), NULL terminated
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
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " \t\n");
}
args[i] = NULL;
return (args);
}

/**
 * main - Simple Shell 0.2 that handles command + arguments
 * Return: 0 on success
 */
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
