/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:44:31 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 10:45:07 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_input_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew("<", '<', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_output_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	node = ft_my_lstnew(">", '>', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}