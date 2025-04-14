#include "main.h"
#include <string.h>

/**
 * main - Entry point of the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	int only_spaces;
	int i;

	while (1)
	{
		line = read_line();
		if (line == NULL) /* Handle Ctrl+D */
		{
			write(1, "\n", 1);
			break;
		}

		/* Check for empty or whitespace-only input */
		only_spaces = 1;
		for (i = 0; line[i]; i++)
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				only_spaces = 0;
				break;
			}
		}

		if (only_spaces)
		{
			free(line);
			continue;
		}

		execute_command(line);
		free(line);
	}

	return (0);
}
