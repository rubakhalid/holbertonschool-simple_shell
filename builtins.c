#include "shell.h"

/**
 * is_builtin - Checks if the command is a built-in.
 * @args: Command and its arguments.
 *
 * Return: 1 if it's a built-in, 0 otherwise.
 */
int is_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "env") == 0)
		return (1);
	return (0);
}

/**
 * handle_builtin - Executes built-in commands.
 * @args: Command and its arguments.
 */
void handle_builtin(char **args)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
	}
}
