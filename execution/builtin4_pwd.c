#include "../minishell.h"


void	ft_pwd(char **env)
{
	int	i;
	char *path;

	i = 0;
	while (env[i])
	{
		path = ft_strstr(env[i], "PWD=");
		if (path != NULL)
			break ;
		i++;
	}
	path += 4;
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

