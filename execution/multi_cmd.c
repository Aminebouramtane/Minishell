/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:50 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/14 19:18:32 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_parce_node *temp, char **envp, char *cmd_path,
						char **env)
{
	run_builtin1(temp, envp, env);
	successful_exit(cmd_path, envp);
}

void	execution_firsts(t_parce_node *temp, char **envp, int *fd, char **env)
{
	pid_t	pid;
	char	*cmd_path;

	cmd_path = NULL;
	pid = fork();
	if (pid == 0)
	{
		into_child(fd);
		open_files_child(temp, envp);
		if (temp && temp->args && check_builtins(temp->args[0]) == 1)
			handle_builtins(temp, envp, cmd_path, env);
		else
		{
			cmd_path = get_cmd_path(temp);
			is_directory_check(temp, cmd_path, envp);
			check_access(temp, cmd_path, envp);
			if (execve(cmd_path, temp->args, envp) == -1)
				execve_error(temp, envp, cmd_path);
			successful_exit(cmd_path, envp);
		}
	}
	else
		back_to_parent(fd);
}

void	execution_last(t_parce_node *temp, char **envp,
						int *fd, char **env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;	

	cmd_path = NULL;
	status = 0;
	pid = fork();
	fork_check(pid);
	if (pid == 0)
	{
		preparing_child(fd, temp, envp);
		if (temp && temp->args)
			child_process(temp, envp, env, cmd_path);
		else
			empty_exit();
	}
	else
	{
		(close(fd[1]), dup2(fd[0], 0), close(fd[0]));
		waiting_signals(pid, status);
	}
}

void	execute_multi(t_parce_node *parce, char **envp, char **env)
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
			execution_firsts(temp, envp, fd, env);
		}
		else
		{
			execution_last(temp, envp, fd, env);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
		}
		temp = temp->next;
	}
	dup2(100, 1);
	dup2(101, 0);
}
