#include "shell.h"

/**
 * find_command - Searches for the full path of a command in the PATH variable
 * @command: The command to locate
 *
 * Return: Full path if found and executable, NULL otherwise
 */
char *find_command(char *command)
{
	char *path_env = NULL;
	char *path_copy, *dir;
	char full_path[1024];
	int i = 0;

	/* Search for PATH variable in the environment */
	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path_env = environ[i] + 5;
			break;
		}
		i++;
	}

	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * has_path_env - Checks if the PATH variable exists in the environment
 *
 * Return: 1 if found, 0 otherwise
 */
int has_path_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}
