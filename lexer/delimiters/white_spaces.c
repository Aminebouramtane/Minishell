/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:56:12 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 08:33:20 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_white_spaces_in_node(char *str, size_t *i, t_vars *data)
{
	t_datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i;
	while (str[end])
	{
		if (str[end] != ' ' && str[end] != '\t')
			break ;
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
