/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:20:58 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/27 16:02:33 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_file(t_parce_node *temp, char **envp)
{
	file_error(temp->file, envp);
	if (envp)
		ft_free(envp);
	ft_malloc(0, 1);
	ft_env_lstclear(g_envi);
	exit(1);
}

void	successful_exit(char *cmd_path, char **envp)
{
	g_envi->exit_status = 0;
	if (cmd_path)
		free(cmd_path);
	ft_free(envp);
	ft_env_lstclear(g_envi);
	ft_malloc(0, 1);
	exit(0);
}

int	open_files_parent(t_parce_node *temp, char **envp)
{
	int	flag;

	flag = 0;
	while (temp->file)
	{
		if (temp->file->redir_in == 1 && handle_in_files(temp, envp))
		{
			file_error(temp->file, envp);
			return (1);
		}
		if (temp->file->heredoc == 1)
			open_files_heredocc(temp->file, 0);
		if (temp->file->redir_out == 1 && handle_out_files(temp, envp))
		{
			file_error(temp->file, envp);
			return (1);
		}
		if (temp->file->append == 1 && handle_append_files(temp, envp))
		{
			file_error(temp->file, envp);
			return (1);
		}
		temp->file = temp->file->next;
	}
	return (flag);
}
