#include "shell.h"

/**
 * handle_cd - Handles the 'cd' command to change the working directory
 * @args: Array of arguments passed (expects args[1] as the path)
 *
 * Return: Nothing
 */
void handle_cd(char **args)
{
	char *path;

	if (args[1] == NULL)
	{
		path = getenv("HOME");
	}
	else
	{
		path = args[1];
	}

	if (chdir(path) != 0)
	{
		perror("cd");
	}
}
