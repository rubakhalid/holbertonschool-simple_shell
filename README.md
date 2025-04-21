# Simple Shell

Simple Shell is a basic UNIX command interpreter written in C. It reads user input, parses it, and executes commands, either in interactive or non-interactive mode.

Features:
- Custom shell prompt
- Command execution using execve
- PATH resolution
- Built-in support for 'exit' and 'env'
- EOF (Ctrl+D) handling
- Interactive and non-interactive support

## File Overview

| File Name             | Description                                       |
|-----------------------|---------------------------------------------------|
| `main.c`              | Entry point of the shell                          |
| `execute_command.c`   | Handles forking and executing commands            |
| `find_command_path.c` | Resolves command paths using `PATH`               |
| `parse_line.c`        | Parses input into command and arguments           |
| `shell.h`             | Header file with function prototypes and macros   |
| `man_1_simple_shell`  | Manual page for the shell                         |
| `AUTHORS`             | Project contributors                              |

## Requirements

- Ubuntu 20.04 LTS
- GCC with the following flags:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Usage Examples
# Interactive Mode
$ ./hsh
$ ls
$ /bin/ls -l
$ env
$ exit

# Non-Interactive Mode
$ echo "/bin/ls" | ./hsh

# Manual Page
$ man ./man_1_simple_shell

# Authors
See the AUTHORS file for contributor names.
