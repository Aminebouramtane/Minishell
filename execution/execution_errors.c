/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:36 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/20 20:52:24 by yimizare         ###   ########.fr       */
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
	if (temp && temp->args)
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
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	handle_command(t_parce_node *temp, char *cmd_path, char **envp)
{
	if (!temp || !temp->args || !temp->args[0])
		return (0);
	if (strcmp(temp->args[0], ".") == 0)
	{
		(void)cmd_path;
		(void)envp;
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		g_envi->exit_status = 2;
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		exit(2);
	}
    if (is_directory(temp->args[0]))
    {
		(void)cmd_path;
		(void)envp;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_envi->exit_status = 126;
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		exit(126);
	}
	return (0);
}
