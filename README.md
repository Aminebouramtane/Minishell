# Minishell

Welcome to the Minishell project! This project is a simple Unix shell created as part of the 42 curriculum. Minishell replicates basic functionalities of a Unix shell, offering an interactive command-line interface to execute commands and manage processes.

## Features

- Basic command execution (e.g., `ls`, `echo`, `cat`, etc.)
- Environment variable handling
- Redirections (`<`, `>`, `>>`)
- Pipes (`|`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS)
- GCC compiler
- GNU Make

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/minishell.git
    ```
2. Navigate to the project directory:
    ```sh
    cd minishell
    ```
3. Compile the project using Make:
    ```sh
    make
    ```

### Running Minishell

After compiling, you can start Minishell by running:
```sh
./minishell

## Usage

Minishell supports a range of commands and features. Here are some examples:

- **Basic Commands**: You can run any executable available in your system's PATH.
    ```sh
    ls -la
    ```
- **Environment Variables**: You can set and unset environment variables using `export` and `unset`.
    ```sh
    export MY_VAR=value
    echo $MY_VAR
    unset MY_VAR
    ```
- **Redirections**: Redirect output to a file or input from a file.
    ```sh
    echo "Hello, World!" > hello.txt
    cat < hello.txt
    ```
- **Pipes**: Use pipes to combine multiple commands.
    ```sh
    ls -la | grep minishell
    ```
- **Built-in Commands**: Utilize built-in commands for shell management.
    ```sh
    cd ..
    pwd
    env
    exit
    ```

## Built-in Commands

### `echo`

Usage:
```sh
echo [options] [string...]

Options:
- `-n`: Do not print the trailing newline.

### `cd`

Usage:
```sh
cd [directory]


<!-- //  readline still reachable: 204,178 bytes in 221 blocks -->

