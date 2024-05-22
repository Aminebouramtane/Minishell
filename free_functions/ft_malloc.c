/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:06:41 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/21 12:05:35 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_malloc_lstclear(t_leaks **lst)
{
	t_leaks	*c;
	t_leaks	*n;

	if (lst && *lst)
	{
		c = *lst;
		while (c)
		{
			n = c->next;
            free(c->add);
			c->add = NULL;
			free(c);
			c = n;
		}
		*lst = NULL;
	}
}

void	ft_malloc_lstadd_back(t_leaks **lst, t_leaks *new)
{
	t_leaks	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_leaks	*malloc_lstnew(void *content)
{
	t_leaks	*my_node;

	my_node = (t_leaks *)malloc(sizeof(t_leaks));
	if (my_node == NULL)
		return (NULL);
	my_node->add = content;
	my_node->next = NULL;
	return (my_node);
}

void    *ft_malloc(int size, int flag)
{
    static  t_leaks *add;
    void    *tmp;
    
    tmp = NULL;
    if (flag)
        ft_malloc_lstclear(&add);
    else
    {
        tmp = malloc(size);
        if (!tmp)
            return (NULL);
        ft_malloc_lstadd_back(&add, malloc_lstnew(tmp));
    }
	return (tmp);
}