#include "../minishell.h"

char	*dirs_paths(char *env_path, t_parce_node *parce)
{
	char	**dirs_path;
	char	*s;
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	s = NULL;
	dirs_path = ft_split(env_path, ':');
	if (parce && parce->args[0])
		command_path = ft_strjoin_path("/", parce->args[0]);
	while (dirs_path[i] != NULL)
	{
		s = ft_strjoin_path(dirs_path[i], command_path);
		if (!access(s, X_OK))
			{
				free(command_path);
				free_split(dirs_path);
				return (s);
			}
		else
			free(s);
		i++;
	}
	if (dirs_path)
		ft_free(dirs_path);
	if (command_path)
		free(command_path);
	return (ft_strdup(""));
}

char	*getpaths(void)
{
	char	*env_paths;
	t_env	*temp;

	temp = envi;
	env_paths = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PATH") == 0)
			break ;
		else
			temp = temp->next;
	}
	if (temp == NULL)
	{
		write(2, "minishell: : No such file or directory\n", 39);
		envi->exit_status = 127;
		exit(127);
		//return (env_paths);
	}
	env_paths = ft_strdup(temp->value);
	return (env_paths);
}

void	execve_error(t_parce_node *temp, char **envp, char *cmd_path)
{
	ft_putstr_fd(temp->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (cmd_path)
		free(cmd_path);
	ft_free(envp);
	envi->exit_status = 127;
	//ft_env_lstclear(envi);
	ft_malloc(0, 1);
	exit(127);
}

void	execution_execve(char *cmd_path, t_parce_node *temp, char **envp)
{
	if (errno == EACCES && (temp->args[0][0] == '/' || temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
			|| (temp->args[0][0] == '.' && temp->args[0][1] == '/')) && !access(temp->args[0], F_OK))
	{
		ft_putstr_fd(temp->args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		//ft_lstclear_env(g_env);
		ft_malloc(0, 1);
		envi->exit_status = 126;
		exit(126);
	}
	if (execve(cmd_path, temp->args, envp) == -1)
		execve_error(temp, envp, cmd_path);
	else
		successful_exit(cmd_path, envp);
}

void	execute_single(t_parce_node *parce, char **envp)
{
	t_parce_node	*temp;
	int				status;
	pid_t			pid;
	char			*cmd_path;

	pid = 0;
	temp = parce;
	status = 0;
	cmd_path = NULL;
	keep_in_out();
	if (temp && temp->args && check_builtins(temp->args[0]) == 1)
	{
		open_and_run(temp);
	}
	else if (temp && temp->args && check_builtins(temp->args[0]) != 1)
	{
		pid = fork();
		if (pid == 0)
		{
			cmd_path = get_cmd_path(temp);
			open_files(temp);
			if (temp->args)
			{
				execution_execve(cmd_path, temp, envp);
			}
			else
				successful_exit(cmd_path, envp);
		}
		else
		{
			waiting(pid, status);
		}
	}
	if (envp)
		free_split(envp);
	return_in_out();
}
