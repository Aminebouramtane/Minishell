#include "../minishell.h"

Datatoken	*ft_my_lstnew(void *content, char type, char state)
{
	Datatoken	*my_node;

	my_node = (Datatoken *) ft_malloc(sizeof(Datatoken), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->cmd = content;
	my_node->type = type;
	my_node->state = state;
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

Datatoken	*ft_my_lstlast(Datatoken *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_my_lstadd_back(Datatoken **lst, Datatoken *new)
{
	Datatoken	*last;

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


void	ft_my_lstclear(Datatoken **lst)
{
	Datatoken	*c;
	Datatoken	*n;

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

void	ft_my_lstdelone(Datatoken *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->cmd);
		free(lst);
	}
}