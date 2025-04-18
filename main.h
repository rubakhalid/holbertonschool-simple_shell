#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

extern char **environ;

/* Function Prototypes */
char *_getenv(const char *name);
char *find_command_path(char *command);
int is_only_whitespace(const char *s);
void parse_line(char *line, char **argv);
void execute_command(char *cmd_path, char **args, char *line);

#endif /* MAIN_H */
