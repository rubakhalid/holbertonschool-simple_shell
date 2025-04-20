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
extern int last_exit_status;

/* Core shell functions */
char *read_line(void);
char **tokenize_input(char *input);
void execute_command(char **args);
char *find_command_path(char *cmd);
void print_prompt(void);
int _strncmp(const char *s1, const char *s2, size_t n);
char *get_path_from_environ(void);

/* Built-in commands */
int is_builtin(char **args);
int handle_builtin(char **args);


#endif
