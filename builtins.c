#include "main.h"

/**
 * handle_builtin - Handles built-in commands like exit and env
 * @args: command arguments
 * @status: pointer to the last exit status
 * @line: input line (for freeing memory)
 * Return: 1 if built-in handled, 0 otherwise
 */
int handle_builtin(char **args, int *status, char *line)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(WEXITSTATUS(*status));
	}
	else if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ && environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1);
	}
	return (0);
}
