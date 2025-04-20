#include "shell.h"

/**
 * execute_command - Forks and executes a command.
 * @args: Null-terminated array of strings (command + arguments).
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path = NULL;

	if (args[0] == NULL)
		return;

	if (is_builtin(args))
	{
		handle_builtin(args);
		return;
	}

	if (access(args[0], X_OK) == 0)
		cmd_path = strdup(args[0]);
	else
		cmd_path = find_command_path(args[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		exit(127);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(cmd_path);
}
