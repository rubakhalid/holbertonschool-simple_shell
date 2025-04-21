#include "shell.h"

/**
 * parse_line - Tokenizes the input line into arguments
 * @line: The input line from user
 *
 * Return: NULL-terminated array of tokens (arguments)
 */
char **parse_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens;
	char *token;

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \n\t");
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \n\t");
	}

	tokens[i] = NULL;
	return (tokens);
}
