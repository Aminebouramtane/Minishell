/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:28 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:54:16 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_dolar_long(Datatoken *node)
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
			node->cmd = ft_my_strjoin(ft_itoa(envi->exit_status), \
			node->cmd + 2);
			return ;
		}
		node->cmd += 1;
		str = node->cmd;
		env = getenv(str);
		if (my_strdup_two(env))
			node->cmd = my_strdup_two(env);
		else
			node->cmd = "\0";
	}
}

void	ft_expand_dolar_single(Datatoken *node)
{
	ft_expand_dolar_single_char(node);
	ft_expand_dolar_long(node);
	ft_expand_dolar_two_chars(node);
}

void	ft_expand_dolar(Datatoken *lst)
{
	Datatoken	*node;

	node = lst;
	while (node)
	{
		if (node->cmd && node->cmd[0] == '$' && node->state != 0)
			ft_expand_dolar_single(node);
		node = node->next;
	}
}

void	ft_expand_home(Datatoken *lst)
{
	Datatoken	*node;
	char		*tmp;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->cmd[0] == '~' && node->state != 0)
		{
			node->cmd += 1;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, node->cmd);
			if (tmp)
				node->cmd = tmp;
			else
				node->cmd--;
		}
		node = node->next;
	}
}

void	ft_expand(Datatoken *lst)
{
	ft_expand_dolar(lst);
	ft_expand_home(lst);
}
