/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:11:02 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/14 18:50:41 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_parce_node *temp, char **envp,
						char **env, char *cmd_path)
{
	if (check_builtins(temp->args[0]) == 1)
		handle_builtins(temp, envp, cmd_path, env);
	else
		exec_com(temp, envp, cmd_path);
}

void	empty_exit(void)
{
	ft_malloc(0, 1);
	ft_env_lstclear(g_envi);
	exit(0);
}

void	preparing_child(int *fd, t_parce_node *temp, char **envp)
{
	(void)fd;
	invalid_expand(temp, envp);
	open_files_child(temp, envp);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
