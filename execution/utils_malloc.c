#include "../minishell.h"

void	ft_env_lstclear(t_env *head)
{
	t_env *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->env_var);
		free(temp->key);
		free(temp->value);
		free(temp);
		temp = NULL;
	}
}

t_env	*ft_export_lstnew(t_parce_node *parce, int i)
{
	t_env	*my_node;

	int j;
	j = 0;
	my_node = (t_env *)malloc(sizeof(t_env));
	if (my_node == NULL)
		return (NULL);
	if (my_node->env_var && parce->args[i])
		my_node->env_var = ft_strdup(parce->args[i]);
	my_node->key = NULL;
	//while (parce->args[i][j] != '\0' && parce->args[i][j] != '=')
		//j++;
	if (parce->args[i][j] == '=')
		my_node->key = ft_substr(parce->args[i], 0, j -1);
	my_node->value = ft_strdup(ft_strchr(parce->args[i], '='));
	my_node->next = NULL;
	my_node->prev = NULL;
	return (my_node);
}

t_env	*ft_env_lstnew(void *content)
{
	t_env	*my_node;

	int	i;
	i = 0;
	my_node = (t_env *)malloc(sizeof(t_env));
	if (my_node == NULL)
		return (NULL);
	my_node->env_var = ft_strdup(content);
	//while ((char)content != '\0' && ((char)content) != '=')
		//j++;
	my_node->key = NULL;
	my_node->value = NULL;
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
