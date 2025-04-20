#include "shell.h"

/**
 * _strncmp - Compares two strings up to n bytes.
 * @s1: First string.
 * @s2: Second string.
 * @n: Number of bytes to compare.
 *
 * Return: 0 if equal, non-zero otherwise.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0')
			break;
	}
	return (0);
}

/**
 * get_path_from_environ - Retrieves the PATH value from environ.
 *
 * Return: Pointer to the PATH string or NULL if not found.
 */
char *get_path_from_environ(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_command_path - Searches for a command in the system PATH.
 * @cmd: The command to find.
 *
 * Return: Full path to the command, or NULL if not found.
 */
char *find_command_path(char *cmd)
{
	char *path = get_path_from_environ();
	char *path_copy, *dir;
	char full_path[BUFFER_SIZE];

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
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
