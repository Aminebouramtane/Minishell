

#include "../minishell.h"

t_parce_node	*ft_parce_lstnew(void *cmd, char *infile, char *outfile, t_file *file)
{
	t_parce_node	*my_node;

	my_node = (t_parce_node *)ft_malloc(sizeof(t_parce_node), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->cmd = cmd;
	my_node->in_file = infile;
	my_node->out_file = outfile;
	my_node->file = file;
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

t_parce_node	*ft_parce_lstlast(t_parce_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_parce_lstadd_back(t_parce_node **lst, t_parce_node *new)
{
	t_parce_node	*last;

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


void	ft_parce_lstclear(t_parce_node **lst)
{
	t_parce_node	*c;
	t_parce_node	*n;

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

void	ft_parce_lstdelone(t_parce_node *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->cmd);
		free(lst);
	}
}

