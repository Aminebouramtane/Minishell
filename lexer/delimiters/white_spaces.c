/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:53:57 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/22 14:50:11 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_white_spaces_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	while (str[end])
	{
		if (str[end] != ' ' && str[end] != '\t')
			break;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	if (data->flag)
		node = ft_my_lstnew(tmp, 'w', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(tmp, 'w', GENERAL);
	
	ft_my_lstadd_back(&(data->ndata), node);
}