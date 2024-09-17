/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:19:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/17 09:55:43 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_envi->exit_status = 130;
}

void	ft_handler2(void)
{
	write(1, "\n", 1);
}

void	ft_handler3(void)
{
	exit(0);
	write(1, "exit\n", 1);
}
int	just_quote(t_datatoken *data)
{
	t_datatoken	*node;
	int			quote_count;
	node = data;
	while (node && node->e_type == 'w')
		node = node->next;

	quote_count = 0;
	while (node && node->cmd && node->cmd[0] == '\'')
	{
		quote_count += ft_strlen(node->cmd);
		node = node->next;
		while (node && node->e_type == 'w')
			node = node->next;
	}
	if (quote_count >= 2 && (quote_count % 2 == 0) && !node)
	{
		ft_putstr_fd("Command '' not found\n", 2);
		g_envi->exit_status = 127;
		return (1);
	}
	node = data;
	quote_count = 0;
	while (node && node->cmd && node->cmd[0] == '\"')
	{
		quote_count += ft_strlen(node->cmd);
		node = node->next;
		while (node && node->e_type == 'w')
			node = node->next;
	}
	if (quote_count >= 2 && (quote_count % 2 == 0) && !node)
	{
		ft_putstr_fd("Command \"\" not found\n", 2);
		g_envi->exit_status = 127;
		return (1);
	}
	return (0);
}


