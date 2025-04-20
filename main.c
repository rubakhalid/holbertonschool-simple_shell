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

	while (1)
	{
		print_prompt();
		input = read_line();
		args = tokenize_input(input);
		execute_command(args);

		free(input);
		free(args);
	}
	return (0);
}
