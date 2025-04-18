#include "main.h"

/**
 * run_command - Finds and executes external commands
 * @args: command arguments
 * @line: input line
 * @status: pointer to the last exit status
 */
void run_command(char **args, char *line, int *status)
{
	char *cmd_path;
	pid_t pid;

	cmd_path = find_command_path(args[0]);
	if (!cmd_path)
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", args[0]);
		*status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
		execute_command(cmd_path, args, line);
	else if (pid > 0)
		wait(status);
	else
		perror("fork");

	free(cmd_path);
}
