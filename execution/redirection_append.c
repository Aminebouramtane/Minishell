/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:58 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:59 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files_heredoc(t_file *file)
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
		envi->exit_status = 1;
		exit(1);
	}
	return (temp->heredoc_file_fd);
}

void	open_files_append(t_file *file, int fd_out)
{
	t_file	*temp;

	temp = file;
	while (temp)
	{
		if (temp->append)
		{
			temp->appended_file_fd = open(temp->file, O_CREAT | O_WRONLY
					| O_APPEND, 0644);
			if (temp->appended_file_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				perror(" ");
				ft_putstr_fd("", 2);
				envi->exit_status = 1;
				exit(1);
			}
			else if (temp->next == NULL)
			{
				dup2(temp->appended_file_fd, fd_out);
			}
		}
		temp = temp->next;
	}
}

void	open_out_files_redir(t_file *file, int fd_out)
{
	t_file	*temp;

	temp = file;
	while (temp)
	{
		if (temp->redir_out)
		{
			temp->out_file_fd = open(temp->file, O_WRONLY
					| O_TRUNC | O_CREAT, 0644);
			if (temp->out_file_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				perror(" ");
				ft_putstr_fd("", 2);
				envi->exit_status = 1;
				exit(1);
			}
			if (temp->next)
				close(temp->out_file_fd);
			else if (temp->next == NULL)
				dup2(temp->out_file_fd, fd_out);
		}
		temp = temp->next;
	}
}

void	open_in_files_redir(t_file *file, int fd_in)
{
	t_file	*temp;

	temp = file;
	while (temp)
	{
		if (temp->redir_in)
		{
			temp->in_file_fd = open(temp->file, O_RDONLY);
			if (temp->in_file_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				perror(" ");
				ft_putstr_fd("", 2);
				envi->exit_status = 1;
				exit(1);
			}
			dup2(temp->in_file_fd, fd_in);
		}
		temp = temp->next;
	}
}
