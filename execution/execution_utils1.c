/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:41 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 22:52:09 by amine            ###   ########.fr       */
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

void	open_files(t_parce_node *temp, char **envp)
{
	while (temp->file)
	{
		if (temp->file->redir_in == 1)
			open_in_files_redir(temp->file, 0, envp);
		if (temp->file->heredoc == 1)
			open_files_heredocc(temp->file, 0);
		if (temp->file->redir_out == 1)
			open_out_files_redir(temp->file, 1, envp);
		if (temp->file->append == 1)
			open_files_append(temp->file, 1, envp);
		temp->file = temp->file->next;
	}
}

void	open_and_run(t_parce_node *temp, char **env)
{
	open_files(temp, env);
	run_builtin(temp, env);
}

char	*get_cmd_path(t_parce_node *temp)
{
	char	*path_env;
	char	*cmd_path;

	path_env = NULL;
	cmd_path = NULL;
	path_env = getpaths(temp);
	if (path_env == NULL)
		return (temp->args[0]);
	cmd_path = dirs_paths(path_env, temp);
	if (path_env != NULL)
		free(path_env);
	return (cmd_path);
}
