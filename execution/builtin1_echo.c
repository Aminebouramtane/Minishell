#include "../minishell.h"

void	echo_without_flag(t_parce_node *parce)
{
	int	i;

	i = 1;
	while (parce->args[i] != NULL)
	{
		ft_putstr_fd(parce->args[i], 1);
		if (parce->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	echo_print(t_parce_node *parce, int i)
{
	while (parce->args[i] != NULL)
	{
		ft_putstr_fd(parce->args[i], 1);
		if (parce->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

void	ft_echo(t_parce_node *parce)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (parce->args[i] == NULL)
		ft_putstr_fd("\n", 1);
	else if (parce->args[1][j] == '-')
	{
		j++;
		if (parce->args[i][j] == '\0')
			echo_without_flag(parce);
		while (parce->args[1][j] != '\0' && (parce->args[1][j] == 'n'))
			j++;
		if (parce->args[i][j] == '\0')
			echo_print(parce, 2);
		else
		{
			echo_print(parce, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	else
		echo_without_flag(parce);
	if (envi)
		envi->exit_status = 0;
}
