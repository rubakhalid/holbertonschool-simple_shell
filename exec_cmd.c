#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Executes a command with no arguments
 * @line: Command line input (single word)
 */
void execute_command(char *line)
{
	pid_t pid;
	char *argv[] = {line, NULL};

	pid = fork();
	if (pid == 0)
	{
		if (execve(line, argv, environ) == -1)
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
