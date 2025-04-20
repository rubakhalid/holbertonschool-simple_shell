#include "shell.h"

/**
 * read_line - Reads a line of input from the user.
 *
 * Return: Pointer to the input string.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		exit(0);  /* Ctrl+D exits */
	}

	return (line);
}
