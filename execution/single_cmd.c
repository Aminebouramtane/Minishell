#include "../minishell.h"


void	free_split(char **command_av)
{
	int	i;

	i = 0;
	while (command_av[i])
	{
		free(command_av[i]);
		i++;
	}
	free(command_av);
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
		write(2, "enviroment PATH not found :\n", 27);
	env_paths = ft_strdup(temp->value);
	return (env_paths);
}

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
		if (!access(s, X_OK | F_OK))
			return (free(command_path), s);
		else
			(free(s), free(dirs_path[i]));
		i++;
	}
	(free_split(dirs_path), free(env_path), free(command_path));
	return(NULL);
}

void	execute_single(t_parce_node *parce, char **envp)
{
	(void)parce;
	(void)envp;

	int pid = fork();
	if (pid == 0)
	{
		char *paths = getpaths();
		char *cmd_path = dirs_paths(paths, parce);
		printf("%s\n", paths);
		if (execve(cmd_path, parce->args ,envp) == -1)
		{
			printf("execve didn't work");
		}
		envi->exit_status = 0;
		exit(0);
	}
	wait(NULL);
}
