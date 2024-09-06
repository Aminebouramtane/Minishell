/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:52:37 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 09:28:52 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand_dolar_single_char(t_datatoken *node)
{
	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
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

void	handle_underscore_case(t_datatoken *node)
{
	char	*env;

	env = my_strdup_two(get_value("_"));
	if (env)
		node->cmd = ft_my_strjoin(env, node->cmd);
	else
		node->cmd = "\0";
}

void	handle_env_variable_case(t_datatoken *node, char *str)
{
	char	*env;

	env = get_value(str);
	if (env || str[0] == '?')
	{
		if (str[0] == '?')
			node->cmd = ft_itoa(envi->exit_status);
		else
			node->cmd = my_strdup_two(env);
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
		else if (node->cmd[1] == '_' && node->e_state != 0)
		{
			handle_underscore_case(node);
			return ;
		}
		node->cmd += 1;
		str = node->cmd;
		handle_env_variable_case(node, str);
	}
}
