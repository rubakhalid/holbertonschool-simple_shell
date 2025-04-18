#include "main.h"

/**
 * execute_cmd - Executes a command by forking and using execve
 * @args: Parsed command arguments
 * @status: Pointer to store exit status
 */
void execute_cmd(char **args, int *status)
{
	pid_t pid;
	char *path;

	if (!args || !args[0])
		return;

	path = find_command_path(args[0]);
	if (!path)
	{
		write(STDERR_FILENO, "./hsh: 1: ", 10);
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 13);
		*status = 127;
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return;
	}
	if (pid == 0)
	{
		execve(path, args, environ);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, status, 0);
		free(path);
	}
}

/**
 * handle_builtin - Handles built-in shell commands
 * @args: Parsed command arguments
 * @line: Original input line (used for exit)
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int handle_builtin(char **args, char *line)
{
	int i = 0;

	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		while (environ[i])
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}
	return (0);
}

/**
 * main - Entry point of the shell program
 * Return: exit status
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[64];
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[0] == '\n' || is_only_whitespace(line))
			continue;

		parse_line(line, args);

		if (handle_builtin(args, line))
			continue;

		execute_cmd(args, &status);
	}

	free(line);
	return (WEXITSTATUS(status));
}
