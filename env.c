#include "main.h"

/**
 * print_env - Prints the current environment variables
 */
void print_env(void)
{
int i = 0;

while (environ[i])
{
write(1, environ[i], strlen(environ[i]));
write(1, "\n", 1);
i++;
}
}
