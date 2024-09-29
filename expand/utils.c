/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:37 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 13:03:39 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_dolar_single_char(t_datatoken *node)
{
	if (node && node->cmd && node->cmd[0] == '$'
		&& (node->e_state == 0 || node->e_state == 1)
		&& ft_strlen(node->cmd) == 1
		&& node->next && (node->next->e_state == 0
			|| node->next->e_state == 1))
		node->cmd = "$";
	else if (node && node->cmd && node->cmd[0] == '$'
		&& ft_strlen(node->cmd) == 1
		&& node->next && (node->next->e_state == 0
			|| node->next->e_state == 1))
		node->cmd = "\0";
	else if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
		node->cmd = "$";
}

void	handle_home_case(t_datatoken *node)
{
	char	*env;

	env = my_strdup_two(get_value("HOME"));
	if (env)
		node->cmd = ft_my_strjoin(env, node->cmd);
	else
		node->cmd = "\0";
}

void	handle_env_variable_case(t_datatoken *node, char *str)
{
	char	*env[2];

	env[0] = get_value(str);
	env[1] = ft_parse_value(env[0]);
	if (env[1] || str[0] == '?')
	{
		if (str[0] == '?' && g_envi)
			node->cmd = ft_itoa(g_envi->exit_status);
		else
			node->cmd = my_strdup_two(env[1]);
	}
	else
		node->cmd = "\0";
}

void	ft_expand_dolar_two_chars(t_datatoken *node)
{
	char	*str;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 2)
	{
		if (ft_isdigit(node->cmd[1]))
		{
			node->cmd = "\0";
			return ;
		}
		else if (node->cmd[1] == '~' && node->e_state != 0)
		{
			handle_home_case(node);
			return ;
		}
		node->cmd += 1;
		str = node->cmd;
		handle_env_variable_case(node, str);
	}
}

void	ft_handle_node_types(t_datatoken **node)
{
	while (*node)
	{
		if (((*node)->e_type == '|' && (*node)->e_state == 2)
			|| ((*node)->e_type == 'w' && (*node)->e_state == 2))
			break ;
		*node = (*node)->next;
	}
}
