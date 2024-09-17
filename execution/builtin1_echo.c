/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:43:58 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/17 19:40:12 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_n_flag(char *arg)
{
	int	j;

	if (arg[0] != '-')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

void	echo_flagged(t_parce_node *parce, int i, int j)
{
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

void	ft_echo(t_parce_node *parce)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (parce->args[i] && is_n_flag(parce->args[i]))
	{
		no_newline = 1;
		i++;
	}
	echo_print(parce, i);
	if (!no_newline)
		ft_putstr_fd("\n", 1);
	if (g_envi)
		g_envi->exit_status = 0;
}

//void	ft_echo(t_parce_node *parce)
//{
//	int	i;
//	int	j;

//	i = 1;
//	j = 0;
//	if (parce->args[i] == NULL)
//		ft_putstr_fd("\n", 1);
//	else if (parce->args[1][j] == '-')
//	{
//		j++;
//		echo_flagged(parce, i, j);
//	}
//	else
//		echo_without_flag(parce);
//	if (g_envi)
//		g_envi->exit_status = 0;
//}
