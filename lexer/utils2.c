/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:20:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 09:29:10 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_datatoken	*ft_my_lstnew(void *content, char type, char state)
{
	t_datatoken	*my_node;

	my_node = (t_datatoken *) ft_malloc(sizeof(t_datatoken), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->cmd = content;
	my_node->e_type = type;
	my_node->e_state = state;
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

t_datatoken	*ft_my_lstlast(t_datatoken *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_my_lstadd_back(t_datatoken **lst, t_datatoken *new)
{
	t_datatoken	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	ft_my_lstclear(t_datatoken **lst)
{
	t_datatoken	*c;
	t_datatoken	*n;

	if (lst && *lst)
	{
		c = *lst;
		while (c)
		{
			n = c->next;
			free(c->cmd);
			free(c);
			c = n;
		}
		*lst = NULL;
	}
}

void	ft_my_lstdelone(t_datatoken *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->cmd);
		free(lst);
	}
}
