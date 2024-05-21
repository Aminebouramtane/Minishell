/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:53:57 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 11:13:43 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_white_spaces_in_node(char *str, int *i, t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	while (str[end])
	{
		if (!in_delimiters(str[end], delimiters))
			break;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_my_lstnew(tmp, 'w', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
}