/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:47:32 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 14:50:48 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_pipe_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("|", '|', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("|", '|', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}