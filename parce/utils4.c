

#include "../minishell.h"

t_file	*ft_file_append_lstnew(char *file, int append)
{
	t_file	*my_node;

	my_node = (t_file *)ft_malloc(sizeof(t_file), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->file = file;
	my_node->redir_in = 0;
	my_node->redir_out = 0;
	my_node->heredoc = 0;
    my_node->append = append;
	my_node->eof = NULL;
	my_node->index = 0;
	my_node->next = NULL;
	my_node->prev = NULL;
	return (my_node);
}

t_file	*ft_file_append_lstlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_file_append_lstadd_back(t_file **lst, t_file *new)
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

