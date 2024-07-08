#include "../minishell.h"

void	open_files_append(t_parce_node *parce)
{
	t_file	*temp;

	temp = parce->file;
	while (temp)
	{
		if (temp->append)
		{
			temp->appended_file_fd = open(temp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (temp->appended_file_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				write(2, ": No such file or directory\n", 28);
				envi->exit_status = 1;
				return ;
			}
			dup2(temp->appended_file_fd, 1);
		}
		temp = temp->next;
	}
}

void	open_out_files_redir(t_parce_node *parce)
{
	t_file	*temp;

	temp = parce->file;
	while (temp)
	{
		if (temp->redir_out)
		{
			temp->out_file_fd = open(temp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (temp->out_file_fd == -1)
			{
				write(2, "minishell: ", 11);
				write(2, temp->file, ft_strlen(temp->file));
				write(2, ": No such file or directory\n", 28);
				envi->exit_status = 1;
				return ;
			}
			dup2(temp->out_file_fd, 1);
		}
		temp = temp->next;
	}
}

void	open_in_files_redir(t_parce_node *parce)
{
	t_file	*temp;

	temp = parce->file;
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
			dup2(temp->in_file_fd, 0);
		}
		temp = temp->next;
	}
}
