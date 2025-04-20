#include "shell.h"

/**
 * tokenize_input - Splits the input string into tokens.
 * @input: The input string.
 *
 * Return: Null-terminated array of strings (tokens).
 */
char **tokenize_input(char *input)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " \t\r\n");
	while (token != NULL)
	{
		tokens[position++] = token;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[position] = NULL;
	return tokens;
}
