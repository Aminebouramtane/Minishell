/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:16:13 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 17:18:17 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	extract_quoted(char *str, size_t start, char **tmp)
{
	size_t	end;

	end = start;
	while (str[end])
	{
		end++;
		if (str[end] == '\'')
		{
			end++;
			break ;
		}
	}
	*tmp = my_strdup(str + start, end - start);
	return (end);
}

void	create_node(char *tmp, size_t *i, size_t end, t_vars *data)
{
	Datatoken	*node;

	if (!check_quotes(tmp) || data->f_qoute == 1)
	{
		node = ft_my_lstnew("'", 's', IN_DOUBLE_COTE);
		ft_my_lstadd_back(&(data->ndata), node);
		*i += 1;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew(tmp, 's', IN_COTE);
		ft_my_lstadd_back(&(data->ndata), node);
		*i = end;
	}
}

void	fill_qoute_in_node(char *str, size_t *i, t_vars *data)
{
	size_t		start;
	size_t		end;
	char		*tmp;

	start = *i;
	tmp = NULL;
	end = extract_quoted(str, start, &tmp);
	create_node(tmp, i, end, data);
}
