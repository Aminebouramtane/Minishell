

#include "../minishell.h"

t_env	*ft_env_lstnew(void *content)
{
	t_env	*my_node;

	my_node = (t_env *)malloc(sizeof(t_env));
	if (my_node == NULL)
		return (NULL);
	my_node->env_var = ft_strdup(content);
	my_node->next = NULL;
	my_node->prev = NULL;
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
	{
		last = last->next;
	}	
	new->prev = last;
	last->next = new;
}
void	ft_env_delone(t_env *lst)
{
	if (!lst)
		return ;
	if (lst)
	{
		free(lst->env_var);
		free(lst);
	}
}
