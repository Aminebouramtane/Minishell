/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:20 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 17:14:00 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_list(t_env *start)
{
	t_env	*export;

	if (start == NULL)
		return (NULL);
	export = malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->env_var = ft_strdup(start->env_var);
	export->key = ft_strdup(start->key);
	export->value = ft_strdup(start->value);
	export->next = copy_list(start->next);
	return (export);
}

int	skip_underscore(t_env	*temp)
{
	if (temp && temp->key && ft_strncmp(temp->key, "_") == 0)
		return (1);
	else
		return (0);
}

void	printlist(t_env *node)
{
	t_env	*temp;

	temp = node;
	if (temp && temp->key && ft_strncmp(temp->key, "PATH") == 0)
		temp = temp->next;
	while (temp != NULL)
	{
		if (skip_underscore(temp) == 1)
		{
			temp = temp->next;
			continue ;
		}
		(ft_putstr_fd("declare -x ", 1), ft_putstr_fd(temp->key, 1));
		if (temp->value != NULL && *temp->value != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else if (ft_strncmp(temp->value, "\0") == 0)
			ft_putstr_fd("=\"\"\n", 1);
		else
			ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
}

void	swap_node_value(t_env *ptr1, char *temp)
{
	temp = ptr1->env_var;
	ptr1->env_var = ptr1->next->env_var;
	ptr1->next->env_var = temp;
	temp = ptr1->key;
	ptr1->key = ptr1->next->key;
	ptr1->next->key = temp;
	temp = ptr1->value;
	ptr1->value = ptr1->next->value;
	ptr1->next->value = temp;
}
