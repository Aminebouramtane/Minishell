/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin6_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:27 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:28 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_exported(t_env	*copy)
{
	copy = copy_list(envi);
	bubblesort(copy);
	printlist(copy);
	ft_env_lstclear(copy);
}

void	copy_and_sort(t_env *copy)
{
	copy = copy_list(envi);
	bubblesort(copy);
	ft_env_lstclear(copy);
}

void	process_arg(t_parce_node *parce, int *i, t_env *temp)
{
	char	*buff;
	t_env	*temp2;

	temp2 = envi;
	buff = ft_strdup(parce->args[i[0]]);
	while (parce->args[i[0]][i[1]] != '\0'
		&& parce->args[i[0]][i[1]] != '='
		&& parce->args[i[0]][i[1]] != '+')
		i[1]++;
	buff[i[1]] = '\0';
	if (valid_key(buff) == 0 || (parce->args[i[0]][i[1]] == '+'
		&& valid_key(buff) == 0))
		ft_env_lstadd_back(&envi, ft_export_lstnew(parce, i[0]));
	else if (valid_key(buff) == 1 && parce->args[i[0]][i[1]] == '+')
		append_the_export(parce, temp, buff, i);
	else if (valid_key(buff) == 1 && parce->args[i[0]][i[1]] == '=')
	{
		while (temp2 && ft_strncmp(temp2->key, buff) != 0)
			temp2 = temp2->next;
		ft_unset_a_node(temp2);
		ft_env_lstadd_back(&envi, ft_export_lstnew(parce, i[0]));
	}
	free(buff);
}

int	valid_export(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		envi->exit_status = 1;
		return (1);
	}
	while (args[i] != '=' && args[i] != '\0' && ft_isalnum(args[i]))
		i++;
	if (args[i] == '=' || args[i] == '\0'
		|| (args[i] == '+' && args[i + 1] != '\0' && args[i + 1] != '+'))
		return (0);
	if (ft_isalnum(args[i]) == 0)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		envi->exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_export(t_parce_node *parce)
{
	t_env	*copy;
	t_env	*temp;
	int		i[2];

	copy = NULL;
	i[0] = 1;
	i[1] = 0;
	temp = envi;
	if (parce->args && parce->args[1] != NULL)
	{
		while (parce && parce->args[i[0]] != NULL)
		{
			if (valid_export(parce->args[i[0]]) == 0)
				process_arg(parce, i, temp);
			i[0]++;
			i[1] = 0;
			temp = envi;
		}
		copy_and_sort(copy);
	}
	else
	{
		show_exported(copy);
	}
}
