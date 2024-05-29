

#include "../minishell.h"

t_file	*ft_file_lstnew(char *file, int redir_in, int redir_out)
{
	t_file	*my_node;

	my_node = (t_file *)ft_malloc(sizeof(t_file), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->file = file;
	my_node->redir_in = redir_in;
	my_node->redir_out = redir_out;
	my_node->heredoc = 0;
	my_node->eof = NULL;
	my_node->index = 0;
	my_node->next = NULL;
	my_node->prev = NULL;
	return (my_node);
}

t_file	*ft_file_lstlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_file_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*last;

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


void	ft_file_lstclear(t_file **lst)
{
	t_file	*c;
	t_file	*n;

	if (lst && *lst)
	{
		c = *lst;
		while (c)
		{
			n = c->next;
			free(c->file);
			free(c);
			c = n;
		}
		*lst = NULL;
	}
}

void	ft_file_lstdelone(t_file *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->file);
		free(lst);
	}
}

