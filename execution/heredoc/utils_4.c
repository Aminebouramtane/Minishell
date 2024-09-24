/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:17:31 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/24 16:03:32 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_expand_h_dolar_two_chars(t_heredoc *node)
{
	char	*str;

	if (node->input[0] == '$' && ft_strlen(node->input) == 2)
	{
		if (ft_isdigit(node->input[1]))
		{
			node->input = "\0";
			return ;
		}
		else if (node->input[1] == '~')
		{
			handle_h_home_case(node);
			return ;
		}
		node->input += 1;
		str = node->input;
		handle_h_env_variable_case(node, str);
	}
}

void	ft_expand_h_dolar_long(t_heredoc *node)
{
	char	*str;
	char	*env;

	if (node->input[0] == '$' && ft_strlen(node->input) > 2)
	{
		if (ft_isdigit(node->input[1]))
		{
			node->input = node->input + 2;
			return ;
		}
		if (node->input[1] == '?')
		{
			node->input = ft_my_strjoin(ft_itoa(g_envi->exit_status), \
			node->input + 2);
			return ;
		}
		node->input += 1;
		str = node->input;
		env = get_value(str);
		if (my_strdup_two(env))
			node->input = my_strdup_two(env);
		else
			node->input = "\0";
	}
}

void	ft_advance_node(t_datatoken **node)
{
	while (*node)
	{
		if (*node && (*node)->e_type == 'w')
			*node = (*node)->next;
		else
			break ;
	}
	while (*node)
	{
		printf("here\n");
		if (*node && (*node)->e_type == '$')
			*node = (*node)->next;
		else
			break ;
	}
}