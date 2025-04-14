#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

/**
 * main - Basic shell that runs commands with full path only
 * Return: Always 0
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t read;
pid_t child_pid;
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

line[strcspn(line, "\n")] = '\0';

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
continue;
}

if (child_pid == 0)
{
argv[0] = line;
argv[1] = NULL;
if (execve(line, argv, environ) == -1)
{
perror("./shell");
exit(EXIT_FAILURE);
}
}
else
{
wait(NULL);
}
}

return (0);
}

