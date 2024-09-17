/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:40:29 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/14 17:31:29 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_syntax_lstsize(t_datatoken *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_datatoken	*initialize_node(t_datatoken *data, int *len)
{
	*len = ft_syntax_lstsize(data);
	return (data);
}

int	handle_final_pipe(t_datatoken *node)
{
	if (node && !node->next && node->e_type == '|' && node->e_state == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	max_herdoc(t_datatoken *node)
{
	int			i;
	t_datatoken	*tmp;

	i = 0;
	tmp = node;
	while (tmp)
	{
		if (i > 16)
			return (1);
		if (tmp->e_type == 'h' && tmp->e_state == 2)
			i++;
		tmp = tmp->next;
	}
	return (0);
}
