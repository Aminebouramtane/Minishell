#include "../minishell.h"

void	exprt_without_value(t_env *my_node, t_parce_node *parce
							, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(buff, 0, iterator[1]);
	my_node->value = NULL;
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	append_exported(t_env *my_node, t_parce_node *parce
						, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(parce->args[iterator[0]], 0, iterator[1]);
	my_node->value = ft_my_strjoin(get_value(buff),
			ft_my_strchr(parce->args[iterator[0]], '='));
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	add_new_export(t_env *my_node, t_parce_node *parce
						, char *buff, int *iterator)
{
	my_node->env_var = ft_strdup(parce->args[iterator[0]]);
	my_node->key = ft_substr(buff, 0, iterator[1]);
	my_node->value = ft_strdup(ft_my_strchr(parce->args[iterator[0]], '='));
	my_node->next = NULL;
	my_node->prev = NULL;
	free(buff);
	buff = NULL;
}

void	*init_node(t_env	*my_node)
{
	my_node = NULL;
	my_node = (t_env *)malloc(sizeof(t_env));
	my_node->env_var = NULL;
	if (!my_node)
		return (NULL);
	my_node->key = NULL;
	my_node->value = NULL;
	return (NULL);
}

char	*ft_my_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i + 1);
}
