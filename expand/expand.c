/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user007 <user007@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:28 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 11:55:09 by user007          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_dolar_long(t_datatoken *node)
{
	char	*str;
	char	*env;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) > 2)
	{
		if (ft_isdigit(node->cmd[1]))
		{
			node->cmd = node->cmd + 2;
			return ;
		}
		if (node->cmd[1] == '?')
		{
			node->cmd = ft_my_strjoin(ft_itoa(g_envi->exit_status), \
			node->cmd + 2);
			return ;
		}
		node->cmd += 1;
		str = node->cmd;
		env = get_value(str);
		if (my_strdup_two(env))
			node->cmd = my_strdup_two(env);
		else
			node->cmd = "\0";
	}
}

void	ft_expand_dolar_single(t_datatoken *node)
{
	ft_expand_dolar_single_char(node);
	ft_expand_dolar_long(node);
	ft_expand_dolar_two_chars(node);
}

void	ft_expand_dolar(t_datatoken *lst)
{
	t_datatoken	*node;

	node = lst;
	while (node)
	{
		if (node->cmd && node->cmd[0] == '$' && node->e_state != 0)
			ft_expand_dolar_single(node);
		node = node->next;
	}
}

void	ft_expand(t_datatoken *lst)
{
	ft_expand_dolar(lst);
}
