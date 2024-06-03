#include "../minishell.h"

void	ft_env(t_env *envi)
{
	int	i;
	t_env	*temp;

	i = 0;
	temp = envi;
	while (temp != NULL)
	{
		ft_putstr_fd(temp->env_var, 1);
		ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}
