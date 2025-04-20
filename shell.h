#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

extern char **environ;

/* Core shell functions */
char *read_line(void);
char **tokenize_input(char *input);
void execute_command(char **args);
char *find_command_path(char *cmd);
void print_prompt(void);

/* Built-in commands */
int is_builtin(char **args);
void handle_builtin(char **args);

#endif
