#include "../minishell.h"

void	check_access(char *cmd_path, char **envp)
{
	if (access(cmd_path, X_OK) != 0)
	{
		if (errno == EACCES && (cmd_path[0] == '/' || cmd_path[ft_strlen(cmd_path) - 1] == '/'
				|| (cmd_path[0] == '.' && cmd_path[1] == '/')) && !access(cmd_path, F_OK))
		{
			ft_putstr_fd(cmd_path, 2);
			ft_putendl_fd(": Permission denied", 2);
			ft_free(envp);
			ft_malloc(0, 1);
			envi->exit_status = 126;
			ft_env_lstclear(envi);
			exit(126);
		}
		else if (errno == ENOENT && (cmd_path[0] == '/' || cmd_path[ft_strlen(cmd_path) - 1] == '/'
				|| (cmd_path[0] == '.' && cmd_path[1] == '/')))
		{
			ft_putstr_fd(cmd_path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			ft_malloc(0, 1);
			ft_free(envp);
			envi->exit_status = 127;
			ft_env_lstclear(envi);
			exit(127);
		}
		else
		{
			ft_putstr_fd(cmd_path, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_free(envp);
			envi->exit_status = 127;
			ft_env_lstclear(envi);
			ft_malloc(0, 1);
			exit(127);
		}
	}
}

int	is_direcotry(char *cmd_path)
{
	int	fd;

	fd = open(cmd_path, __O_DIRECTORY);
	return (fd != -1 && (cmd_path[0] == '/' ||
				((cmd_path[0] == '.') && cmd_path[1] == '/')));
}

void	is_directory_check(char *cmd_path, char **envp)
{
	if (cmd_path)
	{
		if (is_direcotry(cmd_path))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			ft_free(envp);
			ft_malloc(0, 1);
			envi->exit_status = 126;
			ft_env_lstclear(envi);
			exit(126);
		}
	}
}
char	*dirs_paths(char *env_path, t_parce_node *parce)
{
	char	**dirs_path;
	char	*s;
	char	*command_path;
	int		i;

	i = 0;
	command_path = NULL;
	s = NULL;
	dirs_path = NULL;
	dirs_path = ft_split(env_path, ':');
	
	if (parce && parce->args[0] && ft_strchr(parce->args[0], '/'))
		return (ft_strdup(parce->args[0]));
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
	return (NULL);
}

char	*getpaths(t_parce_node *parce)
{
	char	*env_paths;
	t_env	*temp;

	(void)parce;
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parce->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		envi->exit_status = 127;
		exit(127);
		//return (env_paths);
	}
	env_paths = ft_strdup(temp->value);
	return (env_paths);
}

void	execve_error(t_parce_node *temp, char **envp, char *cmd_path)
{
	if (!temp->args[0])
		return	;
	if (errno == EACCES && (temp->args[0][0] == '/' || temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
			|| (temp->args[0][0] == '.' && temp->args[0][1] == '/')) && !access(temp->args[0], F_OK))
	{
		ft_putstr_fd(temp->args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		ft_free(envp);
		free(cmd_path);
		ft_malloc(0, 1);
		envi->exit_status = 126;
		ft_env_lstclear(envi);
		exit(126);
	}
	else if (errno == ENOENT && (temp->args[0][0] == '/' || temp->args[0][ft_strlen(temp->args[0]) - 1] == '/'
			|| (temp->args[0][0] == '.' && temp->args[0][1] == '/')))
	{
		ft_putendl_fd(": No such file or directory", 2);
		ft_free(envp);		
		free(cmd_path);
		ft_malloc(0, 1);
		envi->exit_status = 127;
		ft_env_lstclear(envi);
		exit(127);
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		ft_free(envp);
		free(cmd_path);
		ft_malloc(0, 1);
		envi->exit_status = 127;
		ft_env_lstclear(envi);
		exit(127);
	}
}

void	execution_execve(char *cmd_path, t_parce_node *temp, char **envp)
{
	if (!cmd_path)
		execve_error(temp, envp, cmd_path);
	else if (execve(cmd_path, temp->args, envp) == -1)
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
		open_and_run(temp);
	else if (temp && temp->args && check_builtins(temp->args[0]) != 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (temp && temp->args && check_builtins(temp->args[0]) == 1)
				exit(envi->exit_status);
			open_files(temp);
			cmd_path = get_cmd_path(temp);
			is_directory_check(temp->args[0], envp);
			if (cmd_path && access(cmd_path, X_OK) != 0)
				check_access(temp->args[0], envp);
			if (temp->args)
			{
				execution_execve(cmd_path, temp, envp);
			}
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
