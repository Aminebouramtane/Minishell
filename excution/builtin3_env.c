#include "../minishell.h"

void	ft_env(t_env envi)
{
	int	i;

	i = 0;
	while (envi.my_env[i] != NULL)
	{
		ft_putstr_fd(envi.my_env[i], 1);
		i++;
	}
}
