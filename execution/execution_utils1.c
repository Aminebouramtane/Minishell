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

void	open_files(t_parce_node *temp)
{
	while (temp->file)
	{
		if (temp->file->redir_in == 1)
			open_in_files_redir(temp->file, 0);
		if (temp->file->heredoc == 1)
			open_files_heredocc(temp->file, 0);
		if (temp->file->redir_out == 1)
			open_out_files_redir(temp->file, 1);
		if (temp->file->append == 1)
			open_files_append(temp->file, 1);
		temp->file = temp->file->next;
	}
}

void	open_and_run(t_parce_node *temp, char **env)
{
	open_files(temp);
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
