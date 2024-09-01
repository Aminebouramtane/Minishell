#include "../minishell.h"

t_env	*get_env_vars(char **env_vars)
{
	int	i;

	i = 0;
	while (env_vars && env_vars[i] != NULL)
	{
		ft_env_lstadd_back(&envi, ft_env_lstnew(env_vars[i]));
		i++;
	}
	return (envi);
}

void	ft_env(void)
{
	t_env	*temp;

	temp = envi;
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
	envi->exit_status = 0;
}
