#include "../minishell.h"


static long	ft_strtol(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}


int	valid_estatus(char *status)
{
	int i;
	
	i = 0;
	while(status[i] != '\0' && status[i] == ' ')
		i++;
	if (status[i] != '\0' && (status[i] == '+' || status[i] == '-'))
		i++;
	while (status[i])
	{
		if (!ft_isdigit(status[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_parce_node *parce)
{
	int i;
	int status;
	
	i = 0;
	status = 0;
	
	if (parce->args[1] && !valid_estatus(parce->args[1]))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(parce->args[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		envi->exit_status = 2;
		exit(2);
	}
	if (!parce->args[1])
	{
		ft_putstr_fd("exit\n", 1);
		envi->exit_status = 0;
		exit(0);
	}
	if (parce->args[1] && parce->args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		status = ft_strtol(parce->args[1]);
		envi->exit_status = (int)status;
		exit((int)status);
	}
}
