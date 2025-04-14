#include "main.h"
#include <ctype.h>
#include <string.h>

/**
 * main - Entry point for simple shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		line = trim_spaces(line);
		if (*line == '\0')
			continue;

		execute_command(line);
	}

	free(line);
	return (0);
}


/**
 * trim_spaces - Removes leading and trailing spaces from a string
 * @str: The input string
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	end[1] = '\0';

	return (str);
}
