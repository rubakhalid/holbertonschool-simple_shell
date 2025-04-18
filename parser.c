#include "main.h"

/**
 * parse_line - Splits the input line into tokens (arguments)
 * @line: The input string
 * @argv: The array to store the parsed arguments
 */
void parse_line(char *line, char **argv)
{
	char *token;
	int i = 0;

	token = strtok(line, " \t\n");
	while (token != NULL && i < 63)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	argv[i] = NULL;
}

/**
 * is_only_whitespace - Checks if the line contains only whitespace
 * @s: The input string
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
