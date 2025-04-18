#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* ==== FUNCTION PROTOTYPES ==== */

/* main logic */
void execute_cmd(char **args, int *status);

/* parsing */
void parse_line(char *line, char **argv);
int is_only_whitespace(const char *s);

/* env and path */
char *_getenv(const char *name);
char *find_command_path(char *command);

#endif /* MAIN_H */
