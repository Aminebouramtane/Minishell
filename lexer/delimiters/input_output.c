/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:55:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:55:53 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_check_here_one(Datatoken **node, t_vars *data)
{
	if (data->flag)
		*node = ft_my_lstnew("<<", 'h', IN_DOUBLE_COTE);
	else
		*node = ft_my_lstnew("<<", 'h', GENERAL);
}

void	ft_check_here_two(Datatoken **node, t_vars *data)
{
	if (data->flag)
		*node = ft_my_lstnew(">>", 'a', IN_DOUBLE_COTE);
	else
		*node = ft_my_lstnew(">>", 'a', GENERAL);
}

void	fill_input_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	size_t		a;

	a = *i;
	if (str[a + 1] == '<')
	{
		ft_check_here_one(&node, data);
		a = a + 2;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew("<", '<', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<", '<', GENERAL);
		a++;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	ft_my_lstadd_back(&(data->ndata), node);
}

void	fill_output_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	size_t		a;

	a = *i;
	if (str[a + 1] == '>')
	{
		ft_check_here_two(&node, data);
		a = a + 2;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew(">", '>', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew(">", '>', GENERAL);
		a++;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	ft_my_lstadd_back(&(data->ndata), node);
}
