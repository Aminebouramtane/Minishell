/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:45:07 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/27 21:25:15 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmd(t_datatoken **node, t_parce_node **parce)
{
	while (*node)
	{
		if ((*node)->cmd && (((*node)->cmd[0] == '<' && (*node)->e_type == '<'
					&& (*node)->e_state == 2) || ((*node)->cmd[0] == '>'
					&& (*node)->e_type == '>' && (*node)->e_state == 2)
				|| ((*node)->cmd[0] == '>' && (*node)->e_type == 'a'
					&& (*node)->e_state == 2) || ((*node)->cmd[0] == '<'
					&& (*node)->e_type == 'h' && (*node)->e_state == 2)
				|| ((*node)->e_type == '|' && (*node)->e_state == 2)))
			break ;
		else
			(*parce)->cmd = ft_my_strjoin((*parce)->cmd, (*node)->cmd);
		(*node) = (*node)->next;
	}
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
	if (!*node && (*parce)->args && (*parce)->args[0])
		(*parce)->first = my_strdup_two((*parce)->args[0]);
}

void	initialize_and_traverse_node(t_datatoken **node, char **str, size_t *a)
{
	*str = NULL;
	*a = 0;
	(*node) = (*node)->next;
	while ((*node))
	{
		if (((*node)->e_type == '<' && (*node)->e_state == 2)
			|| ((*node)->e_type == '>' && (*node)->e_state == 2)
			|| ((*node)->e_type == 'a' && (*node)->e_state == 2)
			|| ((*node)->e_type == 'h' && (*node)->e_state == 2)
			|| ((*node)->e_type == 'w' && (*node)->e_state == 2)
			|| ((*node)->e_type == '|' && (*node)->e_state == 2))
			break ;
		else
		{
			if (*node && ((*node)->e_state == 0 || (*node)->e_state == 1))
				*a = 1;
			if ((*node)->cmd[0] == '\'' && (*node)->e_state == 0)
				*str = ft_my_strjoin(*str, ft_remove_qoutes((*node)->cmd));
			else if ((*node)->cmd[0] == '\"' && (*node)->e_state == 1)
				ft_remove_dqoutes(node);
			else
				*str = ft_my_strjoin(*str, (*node)->cmd);
		}
		(*node) = (*node)->next;
	}
}

void	handle_file(t_file **file, int *flag, char *str, size_t a)
{
	char	*name;

	name = "/tmp/heredocc.txt";
	if (a)
		ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 1, str, *flag));
	else
		ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 0, str, *flag));
	if (*file)
		(*file)->index = *flag;
}

void	final_updates(t_datatoken **node, t_parce_node **parce, t_file **file)
{
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void	ft_heredoc(t_datatoken **node,
	t_parce_node **parce, t_file **file, int *flag)
{
	char	*str;
	size_t	a;

	initialize_and_traverse_node(node, &str, &a);
	handle_file(file, flag, str, a);
	final_updates(node, parce, file);
}
