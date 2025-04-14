#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

/**
 * main - Entry point for simple shell that executes single-word commands
 * Return: Always 0 (Success)
 */
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

