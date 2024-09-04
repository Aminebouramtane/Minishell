#include "../minishell.h"

static long long	ft_strtol_check(const char *str)
{
	long long	i;
	long long		sign;
	long long		res;

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
	if (((res > 9223372036854775807) && (sign >= 0))
		|| ((res > 9223372036854775807) && (sign < 0)))
		return (1);
	else
		return (0);
}

static long long	ft_strtol(const char *str)
{
	long long	i;
	size_t		sign;
	size_t		res;

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
	int	i;

	i = 0;
	if (ft_strlen(status) > 19)
		return (0);
	if (ft_strtol_check(status))
		return (0);
	while (status[i] != '\0' && status[i] == ' ')
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

void	exiting(t_parce_node *parce, int status)
{
	ft_putstr_fd("exit\n", 1);
	status = ft_strtol(parce->args[1]);
	envi->exit_status = (int)status;
	ft_malloc(0, 1);
	exit((char)status);
}

void	ft_exit(t_parce_node *parce)
{
	long long	status;

	status = 0;
	if (parce->args[1] && !valid_estatus(parce->args[1]))
		exit_error(parce);
	if (!parce->args[1])
	{
		ft_putstr_fd("exit\n", 1);
		envi->exit_status = 0;
		ft_malloc(0, 1);
		exit(0);
	}
	if (parce->args[1] && parce->args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		envi->exit_status = 1;
	}
	else
	{
		exiting(parce, status);
	}
}
