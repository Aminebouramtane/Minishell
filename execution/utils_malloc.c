#include "../minishell.h"

void	ft_env_lstclear(t_env *head)
{
	t_env	*temp;

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
	char	*buff;
	int		iterator[2];

	buff = NULL;
	my_node = malloc(sizeof(t_env));
	init_node(my_node);
	iterator[0] = i;
	iterator[1] = 0;
	while (parce->args[i][iterator[1]] != '\0' && parce->args[i][iterator[1]] != '='
			&& parce->args[i][iterator[1]] != '+')
		iterator[1]++;
	buff = ft_strdup(parce->args[i]);
	buff[iterator[1]] = '\0';
	if (valid_key(buff) == 0)
	{
		if (parce->args[i][iterator[1]] != '\0' && parce->args[i][iterator[1]] == '=')
			add_new_export(my_node, parce, buff, iterator);
		else if (parce->args[i][iterator[1]] != '\0' && parce->args[i][iterator[1]] == '+')
			add_new_export(my_node, parce, buff, iterator);
		else
			exprt_without_value(my_node, parce, buff, iterator);
	}
	return (my_node);
}

t_env	*ft_env_lstnew(void *content)
{
	t_env	*my_node;
	char	**variable;

	variable = NULL;
	my_node = (t_env *)malloc(sizeof(t_env));
	if (my_node == NULL)
		return (NULL);
	my_node->env_var = ft_strdup(content);
	variable = ft_split(my_node->env_var, '=');
	my_node->key = ft_strdup(variable[0]);
	my_node->value = ft_strdup(variable[1]);
	my_node->next = NULL;
	my_node->prev = NULL;
	ft_free(variable);
	variable = NULL;
	return (my_node);
}

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
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
