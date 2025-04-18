#include "main.h"

#define PROMPT "#cisfun$ "
#define MAX_ARGS 64

/**
 * _getenv - Get the value of an environment variable
 * @name: variable name
 * Return: pointer to value, or NULL
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * find_command_path - Find full path of a command in PATH
 * @command: command name
 * Return: full path if found, NULL otherwise
 */
char *find_command_path(char *command)
{
	char *path_env, *path_copy, *token;
	char full_path[1024];
	struct stat st;

	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
			return (strdup(command));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || path_env[0] == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * is_only_whitespace - Check if a string has only whitespace
 * @s: input string
 * Return: 1 if only whitespace, 0 otherwise
 */
int is_only_whitespace(const char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
			return (0);
		s++;
	}
	return (1);
}

/**
 * main - Simple shell loop
 * Return: exit status
 */
int main(void)
{
	char *line = NULL, *cmd_path;
	size_t len = 0;
	ssize_t read;
	char *args[MAX_ARGS];
	pid_t pid;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		if (is_only_whitespace(line))
			continue;

		parse_line(line, args);
		if (!args[0])
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(WEXITSTATUS(status));
		}

		if (strcmp(args[0], "env") == 0)
		{
			int i = 0;

			while (environ && environ[i])
			{
				printf("%s\n", environ[i]);
				i++;
			}
			continue;
		}

		cmd_path = find_command_path(args[0]);
		if (!cmd_path)
		{
			dprintf(STDERR_FILENO, "./hsh: 1: %s: not found\n", args[0]);
			status = 127;
			continue;
		}

		pid = fork();
		if (pid == 0)
			execute_command(cmd_path, args, line);
		else if (pid > 0)
			wait(&status);
		else
			perror("fork");

		free(cmd_path);
	}
	free(line);
	return (WEXITSTATUS(status));
}
