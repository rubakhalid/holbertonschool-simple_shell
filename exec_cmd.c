#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Executes a command with PATH handling
 * @line: User input line
 */
void execute_command(char *line)
{
pid_t pid;
char *path = getenv("PATH");
char *path_copy = NULL, *token = NULL;
char full_path[1024];
char *argv[64];
int i = 0, found = 0;
char *arg = strtok(line, " ");

while (arg != NULL && i < 63)
{
argv[i++] = arg;
arg = strtok(NULL, " ");
}
argv[i] = NULL;

if (argv[0][0] == '/' || (argv[0][0] == '.' && argv[0][1] == '/'))
{
if (access(argv[0], X_OK) == 0)
{
found = 1;
strcpy(full_path, argv[0]);
}
}
else
{
path_copy = strdup(path);
token = strtok(path_copy, ":");
while (token)
{
snprintf(full_path, sizeof(full_path), "%s/%s", token, argv[0]);
if (access(full_path, X_OK) == 0)
{
found = 1;
break;
}
token = strtok(NULL, ":");
}
free(path_copy);
}

if (!found)
{
write(2, "Command not found\n", 18);
return;
}

pid = fork();
if (pid == 0)
{
execve(full_path, argv, environ);
perror("execve");
exit(EXIT_FAILURE);
}
else if (pid > 0)
{
wait(NULL);
}
}
