#include "../minishell.h"

void	back_to_parent(int *fd)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	execution_single(t_parce_node *temp, char **envp, int *fd)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = NULL;
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		open_files(temp);
		if (temp && temp->args && check_builtins(temp->args[0]) == 1)
		{
			run_builtin(temp);
			successful_exit(cmd_path, envp);
		}
		else
		{
			cmd_path = get_cmd_path(temp);
			if (execve(cmd_path, temp->args, envp) == -1)
				execve_error(temp, envp, cmd_path);
			successful_exit(cmd_path, envp);
		}
	}
	else
		back_to_parent(fd);
}

void	execution_last(t_parce_node *temp, char **envp, int *fd)
{
	pid_t	pid;
	char	*cmd_path;	

	pid = fork();
	cmd_path = get_cmd_path(temp);
	if (pid == 0)
	{
		open_files(temp);
		if (temp && temp->args && check_builtins(temp->args[0]) == 1)
		{
			run_builtin(temp);
			successful_exit(cmd_path, envp);
		}
		else
		{
			if (execve(cmd_path, temp->args, envp) == -1)
				execve_error(temp, envp, cmd_path);
			successful_exit(cmd_path, envp);
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
		if (temp->next != NULL)
		{
			pipe(fd);
			execution_single(temp, envp, fd);
		}
		else
		{
			execution_last(temp, envp, fd);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
		}
		temp = temp->next;
	}
	dup2(100, 1);
	dup2(101, 0);
}
