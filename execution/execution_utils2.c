/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:44 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 17:05:48 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	ft_malloc(0, 1);
	ft_env_lstclear(g_envi);
	exit(131);
}

void	sig_handler2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_envi->exit_status = 130;
}

void	waiting(pid_t pid, int *status)
{
	int	term_signal;

	term_signal = 0;
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
	{
		if (g_envi)
			g_envi->exit_status = WEXITSTATUS(*status);
	}
	if (WIFSIGNALED(*status))
	{
		signal(SIGQUIT, sig_handler);
		term_signal = WTERMSIG(*status);
		if (g_envi)
			g_envi->exit_status = 128 + term_signal;
		if (term_signal == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (term_signal == SIGINT)
			ft_putstr_fd("\n", 1);
	}
}

void	keep_in_out(void)
{
	dup2(0, 100);
	dup2(1, 99);
}

void	return_in_out(void)
{
	dup2(100, 0);
	dup2(99, 1);
}
