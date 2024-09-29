/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:19:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 13:07:30 by abouramt         ###   ########.fr       */
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
	if (g_envi)
		g_envi->exit_status = 130;
}

void	ft_handler3(void)
{
	exit(0);
	write(1, "exit\n", 1);
}

//int	count_quotes(t_datatoken *data, char quote_char)
//{
//	t_datatoken	*node;
//	int			quote_count;

//	node = data;
//	quote_count = 0;
//	while (node && node->e_type == 'w')
//		node = node->next;
//	while (node && node->cmd && node->cmd[0] == quote_char)
//	{
//		quote_count += ft_strlen(node->cmd);
//		node = node->next;
//		while (node && node->e_type == 'w')
//			node = node->next;
//	}
//	return (quote_count);
//}

//int	check_for_unmatched_quotes(int quote_count, char quote_char)
//{
//	if (quote_count >= 2 && (quote_count % 2 == 0))
//	{
//		if (quote_char == '\'')
//			ft_putstr_fd("Command '' not found\n", 2);
//		else if (quote_char == '\"')
//			ft_putstr_fd("Command \"\" not found\n", 2);
//		g_envi->exit_status = 127;
//		return (1);
//	}
//	return (0);
//}

//int	just_quote(t_datatoken *data)
//{
//	int	quote_count;

//	quote_count = count_quotes(data, '\'');
//	if (check_for_unmatched_quotes(quote_count, '\''))
//		return (1);
//	quote_count = count_quotes(data, '\"');
//	if (check_for_unmatched_quotes(quote_count, '\"'))
//		return (1);
//	return (0);
//}
