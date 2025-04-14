#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * execute_command - Executes a command with optional arguments
 * @line: Command line input
 */
void execute_command(char *line)
{
	pid_t pid;
	char *argv[64];
	int i = 0;
	char *token;

	token = strtok(line, " 	");
	while (token != NULL && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " 	");
	}
	argv[i] = NULL;

	if (argv[0] == NULL)
		return;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			perror("hsh");
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
