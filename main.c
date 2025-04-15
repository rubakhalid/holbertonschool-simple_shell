#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* main - Entry point of the simple shell
*
* Return: 0 on success, or EXIT_FAILURE on error
*/
int main(void)
{
char *line = NULL;
int only_spaces;
int i;

while (1)
{
line = read_line();
if (line == NULL)
{
write(1, "\n", 1);
break;
}

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

if (strcmp(line, "exit") == 0)
{
free(line);
exit(0);
}

if (strcmp(line, "env") == 0)
{
print_env();
free(line);
continue;
}

execute_command(line);
free(line);
}

return (0);
}
