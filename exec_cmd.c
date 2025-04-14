#include "main.h"

/**
 * execute_command - Executes a single-word command using fork and execve
 * @line: The input command
 */
void execute_command(char *line)
{
	pid_t pid;
	char *argv[2];

	pid = fork();
	if (pid == 0)
	{
		argv[0] = line;
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
