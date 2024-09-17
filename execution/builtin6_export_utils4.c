/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:23:29 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/12 20:47:02 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_exported(t_env	*copy)
{
	copy = copy_list(g_envi);
	bubblesort(copy);
	printlist(copy);
	ft_env_lstclear(copy);
}

void	copy_and_sort(t_env *copy)
{
	copy = copy_list(g_envi);
	bubblesort(copy);
	ft_env_lstclear(copy);
}

void	process_arg(t_parce_node *parce, int *i, t_env *temp)
{
	char	*buff;
	t_env	*temp2;

	temp2 = g_envi;
	buff = ft_strdup(parce->args[i[0]]);
	while (parce->args[i[0]][i[1]] != '\0'
		&& parce->args[i[0]][i[1]] != '='
		&& parce->args[i[0]][i[1]] != '+')
		i[1]++;
	buff[i[1]] = '\0';
	if (valid_key(buff) == 0 || (parce->args[i[0]][i[1]] == '+'
		&& valid_key(buff) == 0))
		ft_env_lstadd_back(&g_envi, ft_export_lstnew(parce, i[0]));
	else if (valid_key(buff) == 1 && parce->args[i[0]][i[1]] == '+')
		append_the_export(parce, temp, buff, i);
	else if (valid_key(buff) == 1 && parce->args[i[0]][i[1]] == '=')
	{
		while (temp2 && ft_strncmp(temp2->key, buff) != 0)
			temp2 = temp2->next;
		ft_unset_a_node(temp2);
		ft_env_lstadd_back(&g_envi, ft_export_lstnew(parce, i[0]));
	}
	free(buff);
}

void	error_exported(char *args)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_envi->exit_status = 1;
}

int	valid_export(char *args)
{
	int	i;

	i = 0;
	if (args[0] == '=')
	{
		error_exported(args);
		return (1);
	}
	if (!ft_isalpha(args[0]))
	{
		error_exported(args);
		return (1);
	}
	while (args[i] != '=' && args[i] != '\0' && ft_isalnum(args[i]))
		i++;
	if (args[i] == '=' || args[i] == '\0'
		|| (args[i] == '+' && args[i + 1] != '\0' && args[i + 1] != '+'))
		return (0);
	if (ft_isalnum(args[i]) == 0)
	{
		error_exported(args);
		return (1);
	}
	return (0);
}
