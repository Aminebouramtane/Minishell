#include "../minishell.h"

int	open_files_heredoc(t_file *file)
{
	t_file *temp;

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
	//if (dup2(temp->heredoc_file_fd, 0) == -1)
	//{
	//	perror("dup2");
	//	ft_malloc(0, 1);
	//	ft_env_lstclear(envi);
	//	envi->exit_status = EXIT_FAILURE;
	//	exit(EXIT_FAILURE);
	//}
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
			temp->appended_file_fd = open(temp->file, O_WRONLY
					| O_APPEND | O_CREAT, 0644);
			if (envi->out_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				write(2, ": No such file or directory\n", 28);
				envi->exit_status = 1;
				return ;
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
				write(2, ": No such file or directory\n", 28);
				envi->exit_status = 1;
				return ;
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
				write(2, ": No such file or directory\n", 28);
				envi->exit_status = 1;
				return ;
			}
			dup2(temp->in_file_fd, fd_in);
		}
		temp = temp->next;
	}
}
