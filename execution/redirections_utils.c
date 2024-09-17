/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:58:00 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/17 08:18:06 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ambiguous_check(int is_quote, char **envp, char *key)
{
	if ((is_quote == 0) && (!key || key[0] == '\0'))
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		ft_free(envp);
		exit(1);
	}
	if ((is_quote == 0) && (ft_strchr(key, ' ') != NULL))
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		ft_free(envp);
		exit(1);
	}
}

int	ambiguous_check_parent(int is_quote, char *key)
{
	int	flag;

	flag = 0;
	if ((is_quote == 0) && (!key || key[0] == '\0'))
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_envi->exit_status = 1;
		flag = 1;
	}
	if ((is_quote == 0) && (ft_strchr(key, ' ') != NULL))
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_envi->exit_status = 1;
		flag = 1;
	}
	return (flag);
}

void	file_error(t_file *temp, char **envp)
{
	(void)envp;
	write(2, "minishell: ", 11);
	write(2, temp->file, ft_strlen(temp->file));
	perror(" ");
	ft_putstr_fd("", 2);
	g_envi->exit_status = 1;
}

void	invalid_expand(t_parce_node *temp, char **envp)
{
	t_parce_node	*temp1;

	temp1 = temp;
	if (temp1 && !temp1->args)
	{
		ft_malloc(0, 1);
		ft_env_lstclear(g_envi);
		if (envp)
			ft_free(envp);
		exit(0);
	}
}
