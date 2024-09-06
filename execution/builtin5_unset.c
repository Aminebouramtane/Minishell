/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user007 <user007@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:14 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 00:52:43 by user007          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_a_node(t_env *temp)
{
	if (!temp)
		return ;
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		g_envi = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	ft_env_delone(temp);
}

void	ft_unset(t_parce_node *parce)
{
	int		i;
	t_env	*temp;

	i = 1;
	temp = g_envi;
	while (parce->args[i])
	{
		if (!parce || !parce->args || !parce->args[i])
			return ;
		while (temp && temp->key
			&& ft_strncmp(parce->args[i], temp->key) != 0)
			temp = temp->next;
		ft_unset_a_node(temp);
		i++;
		temp = g_envi;
	}
	g_envi->exit_status = 0;
}
