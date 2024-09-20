/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append_parent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:09:25 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/17 18:16:38 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_heredocp(t_file *file, char **envp, int fd)
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

int	open_files_appendp(t_file *file, int fd_out)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->append)
		{
			if (ambiguous_check_parent(temp->is_quoted, temp->file))
				return (0);
			temp->appended_file_fd = open(temp->file, O_CREAT | O_WRONLY
					| O_APPEND, 0644);
			if (temp->appended_file_fd == -1)
			{
				return (1);
			}
			else if (temp->next == NULL)
			{
				dup2(temp->appended_file_fd, fd_out);
			}
		}
		temp = temp->next;
	}
	return (flag);
}

int	open_out_files_redirp(t_file *file, int fd_out)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->redir_out)
		{
			if (ambiguous_check_parent(temp->is_quoted, temp->file))
				return (0);
			temp->out_file_fd = open(temp->file, O_WRONLY
					| O_TRUNC | O_CREAT, 0644);
			if (temp->out_file_fd == -1)
			{
				return (1);
			}
			if (temp->next)
				close(temp->out_file_fd);
			else if (temp->next == NULL)
				dup2(temp->out_file_fd, fd_out);
		}
		temp = temp->next;
	}
	return (flag);
}

int	open_in_files_redirp(t_file *file, int fd_in)
{
	t_file	*temp;
	int		flag;

	flag = 0;
	temp = file;
	while (temp)
	{
		if (temp->redir_in)
		{
			flag = ambiguous_check_parent(temp->is_quoted, temp->file);
			if (flag)
				return (0);
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
	return (flag);
}
