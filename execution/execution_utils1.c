/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:41 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/20 20:03:14 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_files_heredocc(t_file *file, int fd_in)
{
	t_file	*temp;
	int		fd;

	temp = file;
	if (temp->heredoc)
	{
		fd = open(temp->file, O_RDONLY);
		dup2(fd, fd_in);
	}
}

void	infile_redir_child(t_parce_node *temp, int flag, char **envp)
{
	flag = open_in_files_redir(temp->file, 0, envp);
	if (flag == 1)
	{
		free_file(temp, envp);
	}
}

void	open_files_child(t_parce_node *temp, char **envp)
{
	int				flag;
	t_parce_node	*temp1;

	flag = 0;
	temp1 = temp;
	while (temp1->file)
	{
		if (temp1->file->redir_in == 1)
			infile_redir_child(temp1, flag, envp);
		if (temp1->file->heredoc == 1)
			open_files_heredocc(temp1->file, 0);
		if (temp1->file->redir_out == 1)
		{
			flag = open_out_files_redir(temp1->file, 1, envp);
			if (flag == 1)
				free_file(temp1, envp);
		}
		if (temp1->file->append == 1)
		{
			flag = open_files_append(temp1->file, 1, envp);
			if (flag == 1)
				free_file(temp1, envp);
		}
		temp1->file = temp1->file->next;
	}
}

void	open_and_run(t_parce_node *temp, char **envp, char **env)
{
	int	flag;

	flag = open_files_parent(temp, envp);
	if (flag == 0)
	{
		run_builtin1(temp, envp, env);
	}
}

char	*get_cmd_path(t_parce_node *temp, char **envp)
{
	char	*path_env;
	char	*cmd_path;

	path_env = NULL;
	cmd_path = NULL;
	path_env = getpaths(temp, envp);
	if (path_env == NULL)
		return (ft_strdup(temp->args[0]));
	cmd_path = dirs_paths(path_env, temp);
	if (path_env != NULL)
		free(path_env);
	return (cmd_path);
}
