/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:55:59 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:56:00 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_pipe_in_node(size_t *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("|", '|', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("|", '|', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}
