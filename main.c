#include "main.h"
#include <string.h>

/**
 * is_space - Checks if a character is a space or tab
 * @c: The character to check
 * Return: 1 if space or tab, 0 otherwise
 */
int is_space(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * trim_spaces - Removes leading and trailing spaces from a string
 * @str: The input string
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (is_space(*str))
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && is_space(*end))
		end--;

	end[1] = '\0';

	return (str);
}

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
