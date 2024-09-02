/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:55:40 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:55:41 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_env_in_node(char *str, size_t *i, t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	size_t		start;
	size_t		end;

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
	if (data->flag)
		node = ft_my_lstnew(tmp, '$', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(tmp, '$', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
}
