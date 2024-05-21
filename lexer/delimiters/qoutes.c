/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:39:22 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 11:45:59 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_dqoute_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (str[end] == '\"')
		{
			end++;
			break;
		}
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
}

void	fill_qoute_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	node = ft_my_lstnew("'", '\'', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	start = *i + 1;
	end = *i + 1;
	while (str[end])
	{
		if (str[end] == '\'')
			break;
		end++;
	}
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 's', IN_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
	node = ft_my_lstnew("'", '\'', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = end + 1;
}