#include "../minishell.h"

t_env	*copy_list(t_env *start)
{
	t_env	*export;

	if (start == NULL)
		return (NULL);
	export = malloc(sizeof(t_env));
	if (export == NULL)
		return (NULL);
	export->env_var = ft_strdup(start->env_var);
	export->key = ft_strdup(start->key);
	export->value = ft_strdup(start->value);
	export->next = copy_list(start->next);
	return (export);
}


void	printList(t_env *node)
{
	//t_env *temp;

	//temp = node;
	while (node != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->key, 1);
		 if (node->value != NULL)
		{
		 	ft_putstr_fd("=", 1);
		 	ft_putstr_fd("\"", 1);
		 	ft_putstr_fd(node->value, 1);
		 	ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		node = node->next;
	}
}

void	swap_node_value(t_env *ptr1, char *temp)
{
	temp = ptr1->env_var;
	ptr1->env_var = ptr1->next->env_var;
	ptr1->next->env_var = temp;
	temp = ptr1->key;
	ptr1->key = ptr1->next->key;
	ptr1->next->key = temp;
	temp = ptr1->value;
	ptr1->value = ptr1->next->value;
	ptr1->next->value = temp;
}


void	bubbleSort(t_env *start)
{
	int		swapped;
	char	*temp;
	t_env	*ptr1;

	swapped = 1;
	temp = NULL;
	if (start == NULL)
        return;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != NULL)
		{
			if (ft_strncmp(ptr1->env_var, ptr1->next->env_var) > 0)
			{
				swap_node_value(ptr1, temp);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
	}
}


void	ft_export(t_parce_node *parce)
{
	t_env	*temp;
	t_env	*copy;
	int		i;

	i = 1;
	temp = envi;
	if (parce->args && parce->args[1] != NULL)
	{
		while (parce && parce->args[i] != NULL)
		{
			ft_env_lstadd_back(&envi, ft_export_lstnew(parce, i));
			//printList(envi);
			i++;
		}
		copy = copy_list(envi);
		bubbleSort(copy);
		//printList(copy);
		ft_env_lstclear(copy);
	}	
	else
	{
		copy = copy_list(envi);
		bubbleSort(copy);
		printList(copy);
		ft_env_lstclear(copy);
	}
}
