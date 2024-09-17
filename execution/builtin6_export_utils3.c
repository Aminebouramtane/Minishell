/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 17:15:06 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_the_export(t_parce_node *parce, t_env *temp, char *buff, int *i)
{
	while (temp && ft_strncmp(temp->key, buff) != 0)
		temp = temp->next;
	free(temp->value);
	temp->value = NULL;
	temp->value = ft_strjoin_path(get_value(buff),
			ft_my_strchr(parce->args[i[0]], '='));
}

void	bubblesort(t_env *start)
{
	int		swapped;
	char	*temp;
	t_env	*ptr1;

	swapped = 1;
	temp = NULL;
	if (start == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != NULL)
		{
			if (ft_strncmp(ptr1->env_var, ptr1->next->env_var) > 0)
			{
				swap_node_value(ptr1, temp);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
	}
}

int	valid_key(char *key)
{
	t_env	*temp;

	temp = g_envi;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key) != 0)
			temp = temp->next;
		else
			break ;
	}
	if (temp == NULL)
		return (0);
	else
		return (1);
}
