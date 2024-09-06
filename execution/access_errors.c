/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:43:54 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 17:40:54 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	a_permission_error(char *cmd_path, char **envp)
{
	ft_putstr_fd(cmd_path, 2);
	ft_putendl_fd(": Permission denied", 2);
	ft_free(envp);
	if (cmd_path)
		free(cmd_path);
	ft_malloc(0, 1);
	g_envi->exit_status = 126;
	ft_env_lstclear(g_envi);
	exit(126);
}

void	a_no_such_file(char *cmd_path, char **envp)
{
	ft_putstr_fd(cmd_path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	if (cmd_path)
		free(cmd_path);
	ft_free(envp);
	ft_malloc(0, 1);
	g_envi->exit_status = 127;
	ft_env_lstclear(g_envi);
	exit(127);
}

void	a_command_not_found(char *cmd_path, char **envp)
{
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free(envp);
	if (cmd_path)
		free(cmd_path);
	g_envi->exit_status = 127;
	ft_env_lstclear(g_envi);
	ft_malloc(0, 1);
	exit(127);
}

void	check_access(char *cmd_path, char **envp)
{
	if (access(cmd_path, X_OK) != 0)
	{
		if (errno == EACCES && (cmd_path[0] == '/'
				|| cmd_path[ft_strlen(cmd_path) - 1] == '/'
				|| (cmd_path[0] == '.' && cmd_path[1] == '/'))
			&& !access(cmd_path, F_OK))
		{
			a_permission_error(cmd_path, envp);
		}
		else if (errno == ENOENT && (cmd_path[0] == '/'
				|| cmd_path[ft_strlen(cmd_path) - 1] == '/'
				|| (cmd_path[0] == '.' && cmd_path[1] == '/')))
		{
			a_no_such_file(cmd_path, envp);
		}
		else
			a_command_not_found(cmd_path, envp);
	}
}
