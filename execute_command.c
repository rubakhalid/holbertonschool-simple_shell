#include "shell.h"

/**
 * resolve_command_path - Gets the full path of the command.
 * @cmd: Command name.
 *
 * Return: Full path if found, NULL otherwise.
 */
char *resolve_command_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	return (find_command_path(cmd));
}

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

	cmd_path = resolve_command_path(args[0]);
	if (!cmd_path)
	{
	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		exit(127);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror("execve");
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
if (WIFEXITED(status))
	last_exit_status = WEXITSTATUS(status);

	}

	free(cmd_path);
}
