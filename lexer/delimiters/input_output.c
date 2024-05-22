/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:44:31 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 14:51:10 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_input_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;

	if (str[*i + 1] == '<')
	{
		if (data->flag)
			node = ft_my_lstnew("<<", 'h', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<<", 'h', GENERAL);
		*i = *i + 1;
	}
	else
	{		
		if (data->flag)
			node = ft_my_lstnew("<", '<', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<", '<', GENERAL);
	}
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_output_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew(">", '>', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(">", '>', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}