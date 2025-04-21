# 🐚 Simple Shell

A lightweight, custom-built UNIX command-line interpreter written in C.  
It replicates fundamental shell behavior including command parsing, execution, environment handling, and support for built-in commands.

---

## 🚀 Features

- 🧠 Custom shell prompt (`($)`)
- 📂 Command execution using `execve`
- 🔍 PATH resolution for locating executables
- 🧩 Built-in commands: `exit`, `env`
- 💡 Handles End-Of-File (Ctrl+D)
- 🔄 Supports both **interactive** and **non-interactive** modes

---

## 📂 Project Structure

| File Name             | Description                                                  |
|----------------------|--------------------------------------------------------------|
| `main.c`             | Main loop and prompt logic                                   |
| `parse_line.c`       | Splits user input into tokens                                |
| `execute_command.c`  | Handles built-in check, command resolution, and forking      |
| `find_command_path.c`| Resolves command paths using the environment `PATH`          |
| `shell.h`            | Header file with global variables and function prototypes    |
| `man_1_simple_shell` | Manual page for shell usage (see below)                      |
| `AUTHORS`            | Project contributors                                         |

---

## 🛠️ Requirements

- Ubuntu 20.04 LTS
- GCC Compiler

**Compilation:**

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## 🧪 Usage Examples

### 🔸 Interactive Mode
```bash
$ ./hsh
($) ls -l
($) /bin/echo Hello World
($) env
($) exit
```

### 🔹 Non-Interactive Mode
```bash
$ echo "ls -l" | ./hsh
$ cat script.sh | ./hsh
```

---

## 📖 Manual Page

You can access the shell manual using:

```bash
man ./man_1_simple_shell
```

---

## 👩‍💻 Authors

See the [AUTHORS](./AUTHORS) file for a full list of contributors.

---

## 📝 Notes

- Shell supports whitespace trimming and tab separation.
- If a command is not found, an appropriate error message is printed.
- The shell exits with the last command's exit status.

---

## 🔒 License

This project is part of the Holberton School curriculum and intended for educational purposes.
