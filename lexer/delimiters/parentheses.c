/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:42:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 10:43:43 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_open_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("(", '(', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_close_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew(")", ')', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}