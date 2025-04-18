#include "main.h"
#include <string.h>

/**
 * parse_line - Splits a line into tokens (arguments)
 * @line: the full command line input from the user
 * @argv: array to store the resulting arguments
 */
void parse_line(char *line, char **argv)
{
	char *token;
	int i = 0;

	token = strtok(line, " ");
	while (token != NULL && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}
