/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:50 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:51 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_parce_node *temp, char **envp, char *cmd_path)
{
	run_builtin(temp, envp);
	successful_exit(cmd_path, envp);
}

void	execution_firsts(t_parce_node *temp, char **envp, int *fd)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = NULL;
	pid = fork();
	if (pid == 0)
	{
		into_child(fd);
		open_files(temp);
		if (temp && temp->args && check_builtins(temp->args[0]) == 1)
			handle_builtins(temp, envp, cmd_path);
		else
		{
			cmd_path = get_cmd_path(temp);
			is_directory_check(cmd_path, envp);
			check_access(cmd_path, envp);
			if (execve(cmd_path, temp->args, envp) == -1)
				execve_error(temp, envp, cmd_path);
			successful_exit(cmd_path, envp);
		}
	}
	else
		back_to_parent(fd);
}

void	checks(char *cmd_path, char **envp)
{
	is_directory_check(cmd_path, envp);
	check_access(cmd_path, envp);
}

void	execution_last(t_parce_node *temp, char **envp, int *fd)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;	

	pid = fork();
	cmd_path = NULL;
	if (pid == 0)
	{
		open_files(temp);
		if (temp && temp->args && check_builtins(temp->args[0]) == 1)
			handle_builtins(temp, envp, cmd_path);
		else
		{
			cmd_path = get_cmd_path(temp);
			(checks(cmd_path, envp) ,execution_execve(cmd_path, temp, envp));
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			envi->exit_status = WEXITSTATUS(status);
		close(fd[1]);
		close(fd[0]);
	}
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
			execution_firsts(temp, envp, fd);
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
