#include "main.h"

/**
 * execute_command - Executes a command using execve
 * @cmd_path: path to the command
 * @args: arguments to pass to execve
 * @line: original user input
 */
void execute_command(char *cmd_path, char **args, char *line)
{
	(void)line;

	if (access(cmd_path, X_OK) == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		exit(1);
	}
	else
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", args[0]);
		exit(127);
	}
}
