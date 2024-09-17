/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:36 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 20:13:53 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	e_permission_denied(t_parce_node *temp, char *cmd_path, char **envp)
{
	ft_putstr_fd(temp->args[0], 2);
	ft_putendl_fd(": Permission denied", 2);
	ft_free(envp);
	if (cmd_path)
		free(cmd_path);
	ft_malloc(0, 1);
	g_envi->exit_status = 126;
	ft_env_lstclear(g_envi);
	exit(126);
}

void	e_no_such_file(t_parce_node *temp, char *cmd_path, char **envp)
{
	ft_putstr_fd(temp->args[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	ft_free(envp);
	if (cmd_path)
		free(cmd_path);
	ft_malloc(0, 1);
	g_envi->exit_status = 127;
	ft_env_lstclear(g_envi);
	exit(127);
}

void	e_command_not_found(t_parce_node *temp, char *cmd_path, char **envp)
{
	ft_putstr_fd(temp->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	ft_free(envp);
	if (cmd_path)
		free(cmd_path);
	ft_malloc(0, 1);
	g_envi->exit_status = 127;
	ft_env_lstclear(g_envi);
	exit(127);
}

int	is_direcotry(t_parce_node *temp)
{
	int	fd;

	fd = open(temp->args[0], __O_DIRECTORY);
	return (fd != -1 && (temp->args[0][0] == '/'
		|| ((temp->args[0][0] == '.') && temp->args[0][1] == '/')));
}

void	is_directory_check(t_parce_node *temp, char *cmd_path, char **envp)
{
	if (temp->args[0] && temp->args[0][1])
	{
		if (is_direcotry(temp))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			if (envp)
				ft_free(envp);
			if (cmd_path)
				free(cmd_path);
			cmd_path = NULL;
			ft_malloc(0, 1);
			g_envi->exit_status = 126;
			ft_env_lstclear(g_envi);
			exit(126);
		}
	}
}
