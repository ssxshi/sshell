# sshell

A simple command-line shell written in C.

`sshell` is a small educational project built to explore the fundamentals of systems programming and gain hands-on experience with lower-level programming in C.

The goal of this project was to understand how a basic Unix shell works internally, from reading user input and parsing commands to creating processes and executing programs.

## Features

- **Command execution:** Execute external programs using `execvp()`.
- **Process management:** Create child processes using `fork()` and wait for their completion using `waitpid()`.
- **Command parsing:** Read and tokenize user input using `getchar()` and `strtok()`.
- **Built-in commands:**
  - `cd` — Change the current working directory.
  - `help` — Display available built-in commands.
  - `exit` — Exit the shell.
- **Dynamic memory allocation:** Manage input buffers and command tokens using `malloc()` and `realloc()`.

## Getting Started

### Requirements

- A C compiler (GCC or Clang).
- A Unix-like operating system (Linux, macOS, etc.).

### Compilation

Clone the repository:

```bash
git clone https://github.com/ssxshi/sshell.git
cd sshell
```

Compile using GCC:

```bash
gcc sshell.c -o sshell
```

### Running

```bash
./sshell
```

Once running, you can enter commands directly into the shell.

Example:

```text
s@s: help
ssxshi's sshell
Type program names, arguments, and hit enter!
The following commands are built in:
  cd
  help
  exit
Use the [man] command for information on other programs.

s@s: ls
s@s: cd ..
s@s: exit
```

## Learning Objectives

This project was created to get started with systems programming and explore concepts such as:

- Process creation and execution.
- Parent-child process relationships.
- System calls and their role in Unix-like operating systems.
- Pointers and dynamic memory management.
- String manipulation and command parsing.
- The relationship between applications and the operating system.

## Limitations

`sshell` is intentionally minimal and does not aim to replicate a fully featured Unix shell.

Some features not currently supported include:

- Pipes (`|`).
- Input/output redirection (`>`, `<`).
- Command chaining (`&&`, `||`).
- Environment variable expansion.
- Quoted arguments and escape sequences.
- Background processes (`&`).

## Motivation

This project was built for educational purposes as an introduction to systems programming in C.

Rather than relying on existing shell libraries, the goal was to implement the core functionality manually and develop a better understanding of what happens behind the scenes when commands are executed on a Unix-like system.

---

*Built as a learning project.*
