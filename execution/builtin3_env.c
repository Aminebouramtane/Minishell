/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:09 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_arg(t_parce_node *parce)
{
	int		i;
	char	*last_var;

	last_var = NULL;
	i = 0;
	while (parce && parce->next != NULL)
	{
		i = 0;
		while (parce && parce->args[i])
		{
			if (parce->args[i] && parce->args[i + 1] == NULL)
				break ;
			i++;
		}
		parce = parce->next;
	}
	if (parce && parce->args[i])
		last_var = ft_strjoin("_=", parce->args[i]);
	return (last_var);
}

void	last_com_var(t_parce_node *parce)
{
	t_env	*temp;
	char	*arg;
	int		i;

	i = 0;
	temp = envi;
	arg = NULL;
	if (parce->args)
		arg = last_arg(parce);
	else
		arg = ft_strdup("]");
	while (temp && ft_strncmp(temp->key, "_") != 0)
	{
		temp = temp->next;
	}
	if (parce && parce->args && temp && arg)
	{
		ft_unset_a_node(temp);
		ft_env_lstadd_back(&envi, ft_env_lstnew(arg));
	}
	if (arg)
	{
		free(arg);
		arg = NULL;
	}
}

t_env	*get_env_vars(char **env_vars)
{
	int	i;

	i = 0;
	if (env_vars && !env_vars[i])
	{
		ft_env_lstadd_back(&envi, ft_env_lstnew("PATH=/nfs/homes/yimizare/bin:/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("PWD=/nfs/homes/yimizare"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("SHLVL=1"));
		ft_env_lstadd_back(&envi, ft_env_lstnew("_=]"));
	}
	else
	{
		while (env_vars && env_vars[i] != NULL)
		{
			ft_env_lstadd_back(&envi, first_env_lstnew(env_vars[i]));
			i++;
		}
	}
	return (envi);
}

void	print_env(t_env *temp)
{
	while (temp)
	{
		if (temp->value != NULL)
		{
			ft_putstr_fd(temp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

void	ft_env(char **env_vars)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = envi;
	if (env_vars && !env_vars[i])
	{
		while (temp)
		{
			if (temp->value != NULL && ft_strncmp(temp->key, "PATH") != 0)
			{
				ft_putstr_fd(temp->key, 1);
				ft_putchar_fd('=', 1);
				ft_putstr_fd(temp->value, 1);
				ft_putchar_fd('\n', 1);
			}
			temp = temp->next;
		}
	}
	else
	{
		print_env(temp);
	}
	envi->exit_status = 0;
}
