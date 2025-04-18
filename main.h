#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>

extern char **environ;

/* Function Prototypes */
int main(void)
char *read_line(void);
void execute_command(char *line);
void print_prompt(void);
char *_getenv(const char *name);
char *find_command_path(char *command);
char **parse_line(char *line);
int is_only_whitespace(const char *s);
void execute_command(char *line);
char *trim_spaces(char *str);
int is_space(char c);
void parse_line(char *line, char **argv);
void execute_command(char *cmd_path, char **args, char *line);

#endif /* MAIN_H */
