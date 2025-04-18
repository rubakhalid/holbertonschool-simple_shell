#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * execute_command - Executes a command entered by the user
 * @cmd_path: path to the command (can be full or relative)
 * @args: unused
 * @line: full command line input
 */
void execute_command(char *cmd_path, char **args, char *line)
{
	pid_t pid;
	char *argv[64];

	parse_line(line, argv);

	if (argv[0] == NULL)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (access(argv[0], X_OK) == 0)
		{
			execve(argv[0], argv, environ);
			perror("execve");
			exit(1);
		}
		else
		{
			dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", argv[0]);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
