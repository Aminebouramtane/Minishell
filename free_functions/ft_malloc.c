
#include "../minishell.h"

int	free_lstsize(t_leaks *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_leaks	*free_lstlast(t_leaks *lst)
{
	int	last;

	last = free_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}

void	free_lstadd_back(t_leaks **lst, t_leaks *new)
{
	static t_leaks	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = free_lstlast(*lst);
		head->next = new;
	}
}

t_leaks	*free_lstnew(char *value)
{
	t_leaks	*head;

	head = malloc(sizeof(t_leaks));
	if (!head)
		return (NULL);
	head->add = value;
	head->next = NULL;
	return (head);
}

void	free_lstclear(t_leaks **lst)
{
	t_leaks	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		if (*lst)
		{
			if ((*lst)->add)
			{
				free((*lst)->add);
			}
			if (*lst)
				free(*lst);
		}
		*lst = next;
	}
	*lst = NULL;
}

void	*ft_malloc(int size, int flag)
{
	static t_leaks	*address;
	void			*p;
	t_leaks			*new_node;

	p = NULL;
	if (flag)
		free_lstclear(&address);
	else
	{
		p = malloc(size);
		if (!p)
		{
			ft_malloc(0, 1);
			return (NULL);
		}
		new_node = free_lstnew(p);
		if (!new_node)
		{
			free(p);
			p = NULL;
			ft_malloc(0, 1);
			return (NULL);
		}
		free_lstadd_back(&address, new_node);
	}
	return (p);
}
