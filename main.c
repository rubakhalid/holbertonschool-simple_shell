#include "main.h"

/**
 * main - Entry point of the simple shell
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
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			exit(0); /* Handle Ctrl+D */
		}

		line[read - 1] = '\0'; /* Remove newline */

		pid = fork();
		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;

			if (execve(argv[0], argv, NULL) == -1)
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
