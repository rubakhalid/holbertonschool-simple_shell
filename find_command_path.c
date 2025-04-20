#include "shell.h"

/**
 * find_command_path - Searches for a command in the system PATH.
 * @cmd: The command to find.
 *
 * Return: Full path to the command, or NULL if not found.
 */
char *find_command_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char full_path[BUFFER_SIZE];

	if (!path_copy)
		return (NULL);

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
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
