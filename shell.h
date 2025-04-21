#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int has_path_env(void);
char **parse_line(char *line);
int execute_cmd(char **args);
char *find_command(char *command);
void handle_cd(char **args);

extern char **environ;
extern int last_status;

#endif /* SHELL_H */
