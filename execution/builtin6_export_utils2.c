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

void	printlist(t_env *node)
{
	t_env	*temp;

	temp = node;
	if (temp && temp->key && ft_strncmp(temp->key, "PATH") == 0)
		temp = temp->next;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp->key, 1);
		if (temp->value != NULL && *temp->value != '\0')
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else if (ft_strncmp(temp->value, "\0") == 0)
		{
			ft_putstr_fd("=\"\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		temp = temp->next;
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

void	bubblesort(t_env *start)
{
	int		swapped;
	char	*temp;
	t_env	*ptr1;

	swapped = 1;
	temp = NULL;
	if (start == NULL)
		return ;
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

int	valid_key(char *key)
{
	t_env	*temp;

	temp = envi;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key) != 0)
			temp = temp->next;
		else
			break ;
	}
	if (temp == NULL)
		return (0);
	else
		return (1);
}
