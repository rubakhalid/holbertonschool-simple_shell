#include "main.h"

/**
 * is_only_whitespace - Check if a string has only whitespace
 * @s: input string
 * Return: 1 if only whitespace, 0 otherwise
 */
int is_only_whitespace(const char *s)
{
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
			return (0);
		s++;
	}
	return (1);
}
