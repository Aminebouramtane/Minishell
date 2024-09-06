/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:24 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:25 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_the_export(t_parce_node *parce, t_env *temp, char *buff, int *i)
{
	if (parce->args[i[0]][i[1]] == '+')
	{
		while (temp && ft_strncmp(temp->key, buff) != 0)
			temp = temp->next;
		temp->env_var = ft_strdup(parce->args[i[0]]);
		temp->key = ft_substr(parce->args[i[0]], 0, i[1]);
		temp->value = ft_strjoin_path(get_value(buff),
				ft_my_strchr(parce->args[i[0]], '='));
	}
}