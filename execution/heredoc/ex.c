/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:40:17 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/12 09:56:31 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_handle_h_special_case(t_heredoc *node)
{
	if (node->input && node->input[0] && node->input[0] == '$'
		&& ft_strlen(node->input) == 1 && node->next && node->next->input
		&& (node->next->input[0] == '\'' || node->next->input[0] == '\"'))
	{
		node->input = "\0";
	}
}

static void	ft_expand_h_dolar_single(t_heredoc *node)
{
	ft_expand_h_dolar_single_char(node);
	ft_expand_h_dolar_long(node);
	ft_expand_h_dolar_two_chars(node);
}

static void	ft_heredoc_expand_dolar(t_heredoc *lst)
{
	t_heredoc	*node;

	node = lst;
	while (node)
	{
		ft_handle_h_special_case(node);
		if (node->input && node->input[0] == '$')
		{
			ft_expand_h_dolar_single(node);
		}
		node = node->next;
	}
}

void	ft_heredoc_expand(t_heredoc *lst)
{
	ft_heredoc_expand_dolar(lst);
}
