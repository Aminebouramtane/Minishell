/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:20:58 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/15 18:24:41 by yimizare         ###   ########.fr       */
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

void	infile_redir_parent(t_parce_node *temp, char **envp, int flag)
{
	flag = open_in_files_redirp(temp->file, 0);
	if (flag == 1)
		file_error(temp->file, envp);
}

int	open_files_parent(t_parce_node *temp, char **envp)
{
	int	flag;

	flag = 0;
	while (temp->file)
	{
		if (temp->file->redir_in == 1)
			infile_redir_parent(temp, envp, flag);
		if (temp->file->heredoc == 1)
			open_files_heredocc(temp->file, 0);
		if (temp->file->redir_out == 1)
		{
			flag = open_out_files_redirp(temp->file, 1);
			if (flag == 1)
				file_error(temp->file, envp);
		}
		if (temp->file->append == 1)
		{
			flag = open_files_appendp(temp->file, 1);
			if (flag == 1)
				file_error(temp->file, envp);
		}
		temp->file = temp->file->next;
	}
	return (flag);
}
