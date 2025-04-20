#include "shell.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */

int last_exit_status = 0;

int main(void)
{
	char *input;
	char **args;
	int interactive = isatty(STDIN_FILENO);
	int status;

	while (1)
	{
		if (interactive)
			print_prompt();

		input = read_line();
		args = tokenize_input(input);

		if (args[0] == NULL)
		{
			free(input);
			free(args);
			continue;
		}

		status = handle_builtin(args);
		if (status == -1)
		{
			free(input);
			free(args);
			break; /* Exit cleanly */
		}
		else if (status == 1)
		{
			execute_command(args);
		}

		free(input);
		free(args);
	}

	return (0);
}
