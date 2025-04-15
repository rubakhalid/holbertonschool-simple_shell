#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

extern char **environ;

char *read_line(void);
void execute_command(char *line);
void print_prompt(void);
void execute_command(char *line);
char *trim_spaces(char *str);
int is_space(char c);

#endif /* MAIN_H */
