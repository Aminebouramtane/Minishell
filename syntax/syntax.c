/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:29:20 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 14:30:23 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_echo_command(t_datatoken **node)
{
	if (*node && (*node)->next && (ft_strncmp((*node)->cmd, "echo") == 0))
	{
		*node = (*node)->next;
		while (*node && (*node)->cmd && (*node)->cmd[0] == ' '
			&& (*node)->e_state == 2)
			*node = (*node)->next;
		if (!(*node))
			return (0);
		if ((*node)->cmd && ((*node)->cmd[0] == '>' || (*node)->cmd[0] == '<'
				|| ((*node)->cmd[0] == '<' && (*node)->e_type == 'h')
				|| ((*node)->cmd[0] == '>' && (*node)->e_type == 'a')))
		{
			if (!(*node)->next)
			{
				ft_putstr_fd("syntax error near unexpected \
				token `newline'\n", 2);
				return (1);
			}
		}
	}
	return (0);
}

int	handle_pipe_command(t_datatoken *node, int len)
{
	if (node && node->cmd && node->cmd[0] == '|'
		&& node->e_state == 2 && len == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	handle_pipe_redirect(t_datatoken **node)
{
	if (*node && (*node)->next && (*node)->cmd && (*node)->cmd[0] == '|'
		&& (*node)->e_state == 2)
	{
		*node = (*node)->next;
		while ((*node) && (*node)->cmd && (*node)->cmd[0] && (*node)->cmd[0] == ' ' && (*node)->e_state == 2)
			*node = (*node)->next;
		if (!(*node))
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		if ((*node)->cmd && (*node)->cmd[0] == '|' && (*node)->e_state == 2)
		{
			ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
			return (1);
		}
		if ((*node)->cmd && (*node)->cmd[0] == '>' && (*node)->e_state == 2
			&& !(*node)->next)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	handle_final_redirect(t_datatoken *node)
{
	if (node && !node->next && node->cmd
		&& ((node->cmd[0] == '>' && node->e_state == 2)
			|| (node->cmd[0] == '<' && node->e_state == 2)))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	if (node && node->next && node->cmd && ((node->cmd[0] == '>'
				&& node->e_state == 2) || (node->cmd[0] == '<'
				&& node->e_state == 2)))
	{
		node = node->next;
		while (node && node->cmd && node->cmd[0] == ' ' && node->e_state == 2)
			node = node->next;
		if (!node)
			return (0);
		if (node->cmd && (node->cmd[0] == '|' || node->cmd[0] == '>')
			&& node->e_state == 2)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	syntax_err(t_datatoken *data)
{
	t_datatoken	*node;
	int			len;

	node = initialize_node(data, &len);
	while (node)
	{
		if (handle_echo_command(&node) || handle_pipe_command(node, len)
			|| handle_pipe_redirect(&node) || handle_final_redirect(node)
			|| handle_final_pipe(node))
		{
			g_envi->exit_status = 2;
			return (1);
		}
		if (node && node->next)
			node = node->next;
		else
			return (0);
	}
	return (0);
}
