/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:55:56 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 08:32:27 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_open_in_node(size_t *i, t_vars *data)
{
	t_datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("(", '(', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("(", '(', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_close_in_node(size_t *i, t_vars *data)
{
	t_datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew(")", ')', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(")", ')', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}
