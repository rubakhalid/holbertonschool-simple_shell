#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define MAX_ARGS 64

extern char **environ;

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

char *find_command_path(char *command)
{
	char *path_env, *path_copy, *token;
	char full_path[1024];

	if (strchr(command, '/'))
		return (strdup(command));

	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

char **parse_line(char *line)
{
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int i = 0;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

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

int main(void)
{
	char *line = NULL, *cmd_path;
	size_t len = 0;
	ssize_t read;
	char **args;
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

		args = parse_line(line);
		if (!args[0])
		{
			free(args);
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(WEXITSTATUS(status));
		}

		if (strcmp(args[0], "env") == 0)
		{
			int i = 0;
			while (environ[i])
			{
				printf("%s\n", environ[i]);
				i++;
			}
			free(args);
			continue;
		}

		cmd_path = find_command_path(args[0]);
		if (!cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			free(args);
			status = 127;
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(cmd_path, args, environ);
			perror("execve");
			exit(127);
		}
		else if (pid > 0)
		{
			wait(&status);
		}
		else
		{
			perror("fork");
		}

		free(cmd_path);
		free(args);
	}

	free(line);
	return (WEXITSTATUS(status));
}
