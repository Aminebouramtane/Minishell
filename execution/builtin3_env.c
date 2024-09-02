#include "../minishell.h"

t_env	*get_env_vars(char **env_vars)
{
	int	i;

	i = 0;
	if (env_vars && !env_vars[i])
	{
		
		ft_env_lstadd_back(&envi, ft_env_lstnew("PWD=/nfs/homes/yimizare"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("SHLVL=1"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("_=/usr/bin/env"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("PATH=/nfs/homes/yimizare/bin:/usr/local/sbin:/usr/local/bin:\
		/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
		
	}
	else
	{
		while (env_vars && env_vars[i] != NULL)
		{
			ft_env_lstadd_back(&envi, ft_env_lstnew(env_vars[i]));
			i++;
		}
	}
	return (envi);
}

void	ft_env(char **env_vars)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = envi;
	if (env_vars && !env_vars[i])
	{
		while (temp)
		{
			if (temp->value != NULL && ft_strncmp(temp->key, "PATH") != 0)
			{
				ft_putstr_fd(temp->key, 1);
				ft_putchar_fd('=', 1);
				ft_putstr_fd(temp->value, 1);
				ft_putchar_fd('\n', 1);
			}
			temp = temp->next;
		}
	}
	else
	{
		while (temp)
		{
			if (temp->value != NULL)
			{
				ft_putstr_fd(temp->key, 1);
				ft_putchar_fd('=', 1);
				ft_putstr_fd(temp->value, 1);
				ft_putchar_fd('\n', 1);
			}
			temp = temp->next;
		}
	}
	envi->exit_status = 0;
}
