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
    git clone https://github.com/Aminebouramtane/minishell.git
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
```
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
cd [directory]


# <!-- //  readline still reachable: 204,178 bytes in 221 blocks -->

#     // while ((*data)->ndata)
# 	// {
#     //     printf("cmd ## %s state ## %d type ## %c\n", (*data)->ndata->cmd, (*data)->ndata->state, (*data)->ndata->type);
#     //     (*data)->ndata = (*data)->ndata->next;
#     //     // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
# 	// }
#         while (data->ndata)
# 	    {
#            printf("cmd ## %s state ## %d type ## %c\n", data->ndata->cmd, data->ndata->state, data->ndata->type);
#             data->ndata = data->ndata->next;
#             // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
# 	    }
#         // printf("####################PARSING#########################\n");
#         // while (parce) 
# 	    // {
#         //     printf("cmd ## %s\n", parce->cmd);
#         //     if (parce->args)
#         //     {
#         //         i = 0; 
#         //         while (parce->args[i])
#         //         {
#         //            printf("args ## %s\n", parce->args[i]);
#         //             i++;
#         //         }
#         //     }
#         //     while (parce->file)
#         //     {
#         //         printf("-----------FILE : %s\n", parce->file->file);
#         //         printf("-----------REDIRECTION IN : %d\n", parce->file->redir_in);
#         //         printf("-----------REDIRECTION OUT : %d\n", parce->file->redir_out);
#         //         printf("-----------HEREDOC : %d\n", parce->file->heredoc);
#         //         printf("-----------IS_QUOTED : %d\n", parce->file->is_quoted);
#         //         printf("-----------EOF : %s\n", parce->file->eof);
#         //         printf("-----------INDEX : %d\n", parce->file->index);
#         //         printf("======================================\n");
#         //         parce->file = parce->file->next;
#         //     }
#         //     parce = parce->next;
#         //     // <Makefile cat | echo "$PWD 'hola'" ~/src | 'tr' -d  / >outfile
# 	    // } 

#leaks:

    #export | grep PWD
    #pwd | ls
    #export _