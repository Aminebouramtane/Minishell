/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:40:32 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/01 16:40:33 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*ft_heredoc_lstnew(void *content)
{
	t_heredoc	*my_node;

	my_node = (t_heredoc *)ft_malloc(sizeof(t_heredoc), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->input = content;
	my_node->next = NULL;
	return (my_node);
}

t_heredoc	*ft_heredoc_lstlast(t_heredoc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_heredoc_lstadd_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*last;

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

void	ft_heredoc_lstclear(t_heredoc **lst)
{
	t_heredoc	*c;
	t_heredoc	*n;

	if (lst && *lst)
	{
		c = *lst;
		while (c)
		{
			n = c->next;
			free(c->input);
			free(c);
			c = n;
		}
		*lst = NULL;
	}
}

void	ft_heredoc_lstdelone(t_heredoc *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->input);
		free(lst);
	}
}
