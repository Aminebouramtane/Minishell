/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:37 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/03 14:45:24 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_dolar_single_char(Datatoken *node)
{
	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
		node->cmd = "$";
}

void	ft_expand_dolar_two_chars(Datatoken *node)
{
	char	*str;
	char	*env;
	char	*tmp;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 2)
	{
		if (ft_isdigit(node->cmd[1]))
		{
			node->cmd = "\0";
			return ;
		}
		tmp = node->cmd;
		node->cmd += 1;
		str = node->cmd;
		env = get_value(str);
		if (env || str[0] == '?')
		{
			if (str[0] == '?')
				node->cmd = ft_itoa(envi->exit_status);
			else
				node->cmd = my_strdup_two(env);
		}
		else
			node->cmd = "\0";
	}
}
