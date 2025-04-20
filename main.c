#include "shell.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input;
	char **args;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			print_prompt();

		input = read_line();
		args = tokenize_input(input);
		execute_command(args);

		free(input);
		free(args);
	}

	return (0);
}
