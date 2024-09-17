/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:57:20 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/14 18:16:02 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	waiting_signals(pid_t pid, int status)
{
	int	term_signal;

	term_signal = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (g_envi)
			g_envi->exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
	{
		if (WIFSIGNALED(status))
		{
			signal(SIGINT, sig_handler2);
			signal(SIGQUIT, sig_handler);
			term_signal = WTERMSIG(status);
			if (g_envi)
				g_envi->exit_status = 128 + term_signal;
			if (term_signal == SIGQUIT)
				ft_putstr_fd("\n", 2);
			if (term_signal == SIGINT)
				ft_putstr_fd("\n", 1);
		}
	}
}

void	fork_check(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
}

void	pipe_check(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	checks(t_parce_node *parce, char *cmd_path, char **envp)
{
	is_directory_check(parce, cmd_path, envp);
	check_access(parce, cmd_path, envp);
}

void	exec_com(t_parce_node *temp, char **envp, char *cmd_path)
{
	cmd_path = get_cmd_path(temp);
	checks(temp, cmd_path, envp);
	execution_execve(cmd_path, temp, envp);
}
