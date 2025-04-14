#include "main.h"

/**
 * main - A simple shell that executes commands
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		line[read - 1] = '\0'; /* remove newline */

		pid = fork();
		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./hsh");
			}
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	free(line);
	return (0);
}
