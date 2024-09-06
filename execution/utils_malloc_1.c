/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:45:09 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 17:12:28 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*first_env_lstnew(void *content)
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
	my_node->value = ft_strdup(ft_strstr(content, "=") + 1);
	my_node->exit_status = 0;
	my_node->next = NULL;
	my_node->prev = NULL;
	ft_free(variable);
	variable = NULL;
	return (my_node);
}

int	ft_strncmp_env(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((*s1 != '\0' || *s2 != '\0') && (i < n))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
