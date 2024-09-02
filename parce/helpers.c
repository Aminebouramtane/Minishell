/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:03:50 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 14:09:49 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_qoutes(char *lst)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if (lst[0] == '\'')
	{
		lst++;
		while (lst[i] != '\'')
			i++;
		str = my_strdup(lst, i);
	}
	return (str);
}

void	ft_remove_dqoutes(Datatoken **lst)
{
	Datatoken	*node;
	int			flag;

	node = *lst;
	flag = 0;
	while (node)
	{
		if (node->cmd[0] == '\"' && !flag)
		{
			node = node->next;
			flag = 1;
		}
		else if (node->cmd[0] == '\"' && flag)
		{
			node = node->next;
			break ;
		}
		while (node && node->cmd[0] != '\"')
			node = node->next;
	}
}

void	ft_input(Datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;

	str = NULL;
	(*node) = (*node)->next;
	while (*node)
	{
		if (((*node)->type == '<' && (*node)->state == 2)
			|| ((*node)->type == '>' && (*node)->state == 2)
			|| ((*node)->type == 'h' && (*node)->state == 2)
			|| ((*node)->type == 'w' && (*node)->state == 2)
			|| ((*node)->type == '|' && (*node)->state == 2))
			break ;
		else
			str = ft_my_strjoin(str, (*node)->cmd);
		(*node) = (*node)->next;
	}
	process_quotes(str);
	ft_file_lstadd_back(file, ft_file_lstnew(str, 1, 0));
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void	ft_append(Datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;

	str = NULL;
	(*node) = (*node)->next;
	while (*node)
	{
		if (((*node)->type == '<' && (*node)->state == 2)
			|| ((*node)->type == '>' && (*node)->state == 2)
			|| ((*node)->type == 'h' && (*node)->state == 2)
			|| ((*node)->type == 'w' && (*node)->state == 2)
			|| ((*node)->type == '|' && (*node)->state == 2))
			break ;
		else
			str = ft_my_strjoin(str, (*node)->cmd);
		(*node) = (*node)->next;
	}
	process_quotes(str);
	ft_file_lstadd_back(file, ft_file_append_lstnew(str, 1));
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void	ft_output(Datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;

	str = NULL;
	(*node) = (*node)->next;
	while ((*node))
	{
		if (((*node)->type == '<' && (*node)->state == 2)
			|| ((*node)->type == '>' && (*node)->state == 2)
			|| ((*node)->type == 'h' && (*node)->state == 2)
			|| ((*node)->type == 'w' && (*node)->state == 2)
			|| ((*node)->type == '|' && (*node)->state == 2))
			break ;
		else
			str = ft_my_strjoin(str, (*node)->cmd);
		(*node) = (*node)->next;
	}
	process_quotes(str);
	ft_file_lstadd_back(file, ft_file_lstnew(str, 0, 1));
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}
