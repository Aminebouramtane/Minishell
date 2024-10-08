/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:58 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/15 18:20:42 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_heredoc(t_file *file, char **envp, int fd)
{
	t_file	*temp;

	temp = file;
	temp->heredoc_file_fd = open(temp->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (temp->heredoc_file_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file->eof, 2);
		perror(" ");
		ft_putstr_fd("", 2);
		g_envi->exit_status = 1;
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		if (envp)
			ft_free(envp);
		exit(1);
	}
	else
		dup2(temp->heredoc_file_fd, fd);
	return (temp->heredoc_file_fd);
}

int	open_files_append(t_file *file, int fd_out, char **envp)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->append)
		{
			ambiguous_check(temp->is_quoted, envp, temp->file);
			temp->appended_file_fd = open(temp->file, O_CREAT | O_WRONLY
					| O_APPEND, 0644);
			if (temp->appended_file_fd == -1)
			{
				flag = 1;
				return (flag);
			}
			else if (temp->next == NULL)
			{
				dup2(temp->appended_file_fd, fd_out);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	open_out_files_redir(t_file *file, int fd_out, char **envp)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->redir_out)
		{
			ambiguous_check(temp->is_quoted, envp, temp->file);
			temp->out_file_fd = open(temp->file, O_WRONLY
					| O_TRUNC | O_CREAT, 0644);
			if (temp->out_file_fd == -1)
			{
				flag = 1;
				return (flag);
			}
			if (temp->next)
				close(temp->out_file_fd);
			else if (temp->next == NULL)
				dup2(temp->out_file_fd, fd_out);
		}
		temp = temp->next;
	}
	return (0);
}

int	open_in_files_redir(t_file *file, int fd_in, char **envp)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->redir_in)
		{
			ambiguous_check(temp->is_quoted, envp, temp->file);
			temp->in_file_fd = open(temp->file, O_RDONLY);
			if (temp->in_file_fd == -1)
			{
				flag = 1;
				return (flag);
			}
			dup2(temp->in_file_fd, fd_in);
		}
		temp = temp->next;
	}
	return (0);
}
