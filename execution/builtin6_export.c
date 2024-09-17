/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:27 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 17:29:11 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_value_export(t_env *temp)
{
	if (temp->value != NULL && *temp->value != '\0')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(temp->value, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else if (ft_strncmp(temp->value, "\0") == 0)
	{
		ft_putstr_fd("=\"\"\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}

void	print_copy(t_env *node)
{
	t_env	*temp;

	temp = node;
	while (temp != NULL)
	{
		if (temp && temp->key && ft_strncmp(temp->key, "PATH") == 0)
		{
			temp = temp->next;
			continue ;
		}
		if (skip_underscore(temp) == 1)
		{
			temp = temp->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->key, 1);
		print_value_export(temp);
		temp = temp->next;
	}
}

void	export_envless(t_env *copy)
{
	copy = copy_list(g_envi);
	bubblesort(copy);
	print_copy(copy);
	ft_env_lstclear(copy);
}

void	exporting(t_parce_node *parce, int *i, t_env *temp)
{
	while (parce && parce->args[i[0]] != NULL)
	{
		if (valid_export(parce->args[i[0]]) == 0)
			process_arg(parce, i, temp);
		i[0]++;
		i[1] = 0;
		temp = g_envi;
	}
}

void	ft_export(t_parce_node *parce, char **env)
{
	t_env	*copy;
	t_env	*temp;
	int		j;
	int		i[2];

	copy = NULL;
	j = 0;
	i[0] = 1;
	i[1] = 0;
	temp = g_envi;
	if (parce->args && parce->args[1] != NULL)
	{
		exporting(parce, i, temp);
	}
	else
	{
		if (env && !env[j])
			export_envless(copy);
		else
			show_exported(copy);
	}
}
