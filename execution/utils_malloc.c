

#include "../minishell.h"

t_env	*ft_env_lstnew(void *content)
{
	t_env	*my_node;

	my_node = (t_env *)ft_malloc(sizeof(t_env), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->env_var = content;
	my_node->next = NULL;
	return (my_node);
}

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

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