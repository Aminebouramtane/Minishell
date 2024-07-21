#include "../minishell.h"

void execution_single(t_parce_node *temp, char **envp, int *fd)
{
    char *error_msg = NULL;
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        while (temp->file)
        {
            if (temp->file->redir_in == 1)
                open_in_files_redir(temp->file, 0);    
            if (temp->file->redir_out == 1)
                open_out_files_redir(temp->file, fd[1]);
            if (temp->file->append == 1)
                open_files_append(temp->file, fd[1]);
            temp->file = temp->file->next;
        }
        if (temp && temp->args && check_builtins(temp->args[0]) == 1)
        {
            run_builtin(temp);
            exit(0);
        } 
        else
        {
            char *path_env = getpaths();
            char *cmd_path = dirs_paths(path_env, temp);
            if (execve(cmd_path, temp->args, envp) == -1)
            {
                error_msg = ft_strjoin("Minishell: command not found: ", temp->args[0]);
                write(2, error_msg, ft_strlen(error_msg));
                write(2, "\n", 1);
                free(error_msg);
                free_split(envp);
                free(cmd_path);
                envi->exit_status = 1;
                exit(1);
            }
            free_split(envp);
            free(cmd_path);
            envi->exit_status = 0;
            exit(0);
        }
         exit(0);
    }
    else // Parent process
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
}

void execution_last(t_parce_node *temp, char **envp, int *fd)
{
    char *error_msg = NULL;
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        while (temp->file)
        {
            if (temp->file->redir_in == 1)
                open_in_files_redir(temp->file, 0);    
            if (temp->file->redir_out == 1)
                open_out_files_redir(temp->file, 1);
            if (temp->file->append == 1)
                open_files_append(temp->file, 1);
            temp->file = temp->file->next;
        }
        if (temp && temp->args && check_builtins(temp->args[0]) == 1)
        {
            run_builtin(temp);
            exit(0);
        } 
        else
        {
            char *path_env = getpaths();
            char *cmd_path = dirs_paths(path_env, temp);
            if (execve(cmd_path, temp->args, envp) == -1)
            {
                error_msg = ft_strjoin("Minishell: command not found: ", temp->args[0]);
                write(2, error_msg, ft_strlen(error_msg));
                write(2, "\n", 1);
                free(error_msg);
                free_split(envp);
                free(cmd_path);
                envi->exit_status = 1;
                exit(1);
            }
            free_split(envp);
            free(cmd_path);
            envi->exit_status = 0;
            exit(0);
        }
    }
    close(fd[1]);
    close(fd[0]);
}

void	execute_multi(t_parce_node *parce, char **envp)
{
    t_parce_node	*temp;
    int				fd[2];
    int				input_fd;

    temp = parce;
    dup2(1, 100);
    dup2(0, 101);
    input_fd = STDIN_FILENO;
    while (temp != NULL)
    {
        if (temp->next != NULL) // If there's a next command, set up a pipe
        {
            pipe(fd);
            execution_single(temp, envp, fd); // Write end of the pipe
        }
        else // Last command or single command
        {
            execution_last(temp, envp, fd); // Output goes to STDOUT
            if (input_fd != STDIN_FILENO)
                close(input_fd); // Close input_fd if it's not STDIN
        }
        temp = temp->next;
    }
    dup2(100, 1);
    dup2(101, 0);
}
