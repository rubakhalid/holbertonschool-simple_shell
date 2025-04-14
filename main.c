#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * is_space - Checks if character is whitespace
 * @c: Character to check
 * Return: 1 if space/tab, 0 otherwise
 */
int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

/**
 * trim_spaces - Trims leading/trailing spaces
 * @str: String to trim
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
    char *end;

    if (!str) return (NULL);

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
 * main - Simple shell entry point
 * Return: 0 on success, EXIT_FAILURE on error
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "($) ", 4);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            exit(EXIT_SUCCESS);
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        line = trim_spaces(line);
        if (line == NULL || *line == '\0')
            continue;

        if (execute_command(line) == -1)
        {
            free(line);
            exit(EXIT_FAILURE);
        }
    }

    free(line);
    return (EXIT_SUCCESS);
}
