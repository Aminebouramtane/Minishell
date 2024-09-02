/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:56:09 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:57:56 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_string_in_node(char *str, size_t *i,
	t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (in_delimiters(str[end], delimiters))
			break ;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	if (data->flag == 1)
		node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	else if (data->flag == 2)
		node = ft_my_lstnew(tmp, 's', IN_COTE);
	else
		node = ft_my_lstnew(tmp, 's', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
}
