/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:11:02 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/21 13:33:28 by abouramt         ###   ########.fr       */
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

void	empty_exit(char **envp)
{
	if (envp)
		ft_free(envp);
	ft_malloc(0, 1);
	ft_env_lstclear(g_envi);
	exit(0);
}

int	alone_quotesp(t_parce_node *temp)
{
	if (temp && temp->args && temp->args[0]
		&& ft_strncmp(temp->args[0], "\0") == 0)
	{
		ft_putendl_fd("Command '' not found haha", 2);
		g_envi->exit_status = 127;
		return (1);
	}
	else
		return (0);
}

void	preparing_child(int *fd, t_parce_node *temp, char **envp)
{
	(void)fd;
	open_files_child(temp, envp);
	invalid_expand(temp, envp);
	if (temp && temp->args && temp->args[0]
		&& ft_strncmp(temp->args[0], "\0") == 0)
	{
		ft_putendl_fd("Command '' not found hehe", 2);
		ft_free(envp);
		ft_malloc(0, 1);
		g_envi->exit_status = 127;
		ft_env_lstclear(g_envi);
		exit(127);
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
