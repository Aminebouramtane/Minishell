/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:42:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 14:50:54 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_open_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("(", '(', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("(", '(', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_close_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
	{
		node = ft_my_lstnew(")", ')', IN_DOUBLE_COTE);
		data->flag = 0;
	}
	else
		node = ft_my_lstnew(")", ')', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}