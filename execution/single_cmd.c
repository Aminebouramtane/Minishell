#include "../minishell.h"

char	*dirs_paths(char *env_path, t_parce_node *parce)
{
	char	**dirs_path;
	char	*s;
	char	*command_path;
	int		i;

	i = 0;
	dirs_path = ft_split(env_path, ':');
	command_path = ft_strjoin_path("/", parce->args[0]);
	while (dirs_path[i] != NULL)
	{
		s = ft_strjoin_path(dirs_path[i], command_path);
		if (!access(s, X_OK))
			return (free(command_path), s);
		else
			(free(s));
		i++;
	}
	(free_split(dirs_path), free(env_path), free(command_path));
	return(NULL);
}

char	*getpaths()
{
	char	*env_paths;
	t_env	*temp;

	temp = envi;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PATH") == 0)
			break ;
		else
			temp = temp->next;
	}
	if (temp == NULL)
	{
		write(2, "minishell: ls: No such file or directory\n", 41);
		envi->exit_status = 127;
	}	
	env_paths = ft_strdup(temp->value);
	return (env_paths);
}

void	execute_single(t_parce_node *parce, char **envp)
{
	int pid = fork();
	char	*error_msg;

	error_msg = NULL;
	if (pid == 0)
	{
		while (parce->file)
		{
			if (parce->file->redir_in)
				open_in_files_redir(parce);
			if (parce->file->redir_out)
				open_out_files_redir(parce);
			if (parce->file->append)
				open_files_append(parce);
			parce->file = parce->file->next;
		}
		if (check_builtins(parce->args[0]) == 1)
				run_builtin(parce);
		else
		{
			char *path_env = getpaths();
			char *cmd_path = dirs_paths(path_env, parce);
			if (execve(cmd_path, parce->args ,envp) == -1)
			{
				error_msg = ft_strjoin("Minishell: command not found: ", parce->args[0]);
				write(2, error_msg, ft_strlen(error_msg));
				write(2, "\n", 1);
				free(error_msg);
				free_split(envp);
				free(cmd_path);
				envi->exit_status = 1;
				exit(1);
			}
			free_split(envp);
			envi->exit_status = 0;
			exit(0);
		}
	}
	wait(NULL);
}
