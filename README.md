# Simple Shell

## Description

This project is a simple UNIX command-line interpreter written in C.  
It replicates basic shell behavior by interpreting and executing user commands in both interactive and non-interactive modes.  
Developed as part of the Holberton School curriculum, this shell focuses on fundamental system-level programming concepts.

---

## Features

- Displays a custom prompt and waits for user input.
- Executes commands using `execve`.
- Supports commands with arguments (e.g., `ls -l /tmp`).
- Searches for commands in the system's `PATH` environment variable.
- Handles the end-of-file (EOF) condition (e.g., `Ctrl+D`).
- Built-in command: `exit` to terminate the shell.
- Built-in command: `env` to display current environment variables.
- Handles errors gracefully, with custom error messages when commands fail.
- Supports both interactive and non-interactive modes (e.g., via piping).
- Fully compliant with the Betty coding style.
- Modular codebase with separate files for handling input, execution, built-ins, and environment.

---

## File Structure

| File | Description |
|------|-------------|
| `main.c` | Entry point, runs the main shell loop |
| `prompt.c` | Displays prompt and reads user input |
| `exec.c` | Parses and executes commands |
| `path.c` | Locates executables using the PATH variable |
| `builtins.c` | Handles built-in commands like `exit` and `env` |
| `man_1_simple_shell` | Manual page for the shell |
| `AUTHORS` | List of contributors |
| `README.md` | Project documentation |

---

## Requirements

- Ubuntu 20.04 LTS
- GCC version 9.x or later
- Code must pass all Betty style checks

---

## Usage

```bash
$ ./simple_shell
$ ls
$ /bin/ls -l
$ env
$ exit

Non-interactive mode:
bash
نسخ
تحرير
$ echo "/bin/ls" | ./simple_shell
Manual Page
To view the shell's manual page:

bash
نسخ
تحرير
man ./man_1_simple_shell
Authors
See the AUTHORS file for a list of contributors.

License
This project is part of the Holberton School curriculum and follows its academic licensing policies.


