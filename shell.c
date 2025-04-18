#include "main.h"

#define PROMPT "#cisfun$ "
#define MAX_ARGS 64

/**
 * main - Simple shell loop
 * Return: exit status
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[MAX_ARGS];
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

		if (handle_builtin(args, &status, line))
			continue;

		run_command(args, line, &status);
	}
	free(line);
	return (WEXITSTATUS(status));
}
