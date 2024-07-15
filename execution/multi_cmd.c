#include "../minishell.h"

void	execution_single(t_parce_node *temp, char **envp, int *fds)
{
	char *error_msg;

	error_msg = NULL;
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], 0);
		while (temp->file)
			{
				if (temp->file->redir_in == 1)
				{
					open_in_files_redir(temp->file, fds[0]);
				}	
				if (temp->file->redir_out == 1)
				{
					open_out_files_redir(temp->file, fds[1]);
				}	
				if (temp->file->append == 1)
				{
					open_files_append(temp->file, fds[1]);
				}
				temp->file = temp->file->next;
			}
		if (check_builtins(temp->args[0]) == 1)
		{
			run_builtin(temp);
		}
		else
		{
			char *path_env = getpaths();
			char *cmd_path = dirs_paths(path_env, temp);
			if (execve(cmd_path, temp->args ,envp) == -1)
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
			envi->exit_status = 0;
			exit(0);
		}
	}	
}

void	execute_multi(t_parce_node *parce, char **envp)
{
	(void)parce;
	(void)envp;
	t_parce_node *temp;

	int fds[2];
	int input;
	int output;

	input = dup(0);
	output = dup(1);
	pipe(fds);
	temp = parce;
	while (temp)
	{
		
		execution_single(temp, envp, fds);
		temp = temp->next;
	}
	dup2(input, 0);
	dup2(output, 1);
}
