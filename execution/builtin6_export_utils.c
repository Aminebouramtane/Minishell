/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:17 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/10 15:06:32 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exprt_without_value(t_env *my_node, t_parce_node *parce
							, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(buff, 0, iterator[1]);
	my_node->value = NULL;
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	append_exported(t_env *my_node, t_parce_node *parce
						, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(parce->args[iterator[0]], 0, iterator[1]);
	my_node->value = ft_my_strjoin(get_value(buff),
			ft_my_strchr(parce->args[iterator[0]], '='));
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	add_new_export(t_env *my_node, t_parce_node *parce
						, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(buff, 0, iterator[1]);
	my_node->value = ft_strdup(ft_my_strchr(parce->args[iterator[0]], '='));
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	*init_node(t_env	*my_node)
{
	if (!my_node)
		return (NULL);
	my_node->env_var = NULL;
	my_node->key = NULL;
	my_node->value = NULL;
	my_node->exit_status = 0;
	return (NULL);
}

char	*ft_my_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i + 1);
}
