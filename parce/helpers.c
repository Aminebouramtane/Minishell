/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:03:50 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/10 17:41:51 by yimizare         ###   ########.fr       */
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

void	ft_remove_dqoutes(t_datatoken **lst)
{
	t_datatoken	*node;
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

void	ft_input(t_datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;
	int		a;

	str = NULL;
	a = 0;
	(*node) = (*node)->next;
	while (*node)
	{
		if (ft_break(node))
			break ;
		else
		{
			if (*node && ((*node)->e_state == 0 || (*node)->e_state == 1))
				a = 1;
			str = ft_my_strjoin(str, (*node)->cmd);
		}
		(*node) = (*node)->next;
	}
	input_file(file, str, a);
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void	ft_append(t_datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;
	int		a;

	str = NULL;
	a = 0;
	(*node) = (*node)->next;
	while (*node)
	{
		if (ft_break(node))
			break ;
		else
		{
			if (*node && ((*node)->e_state == 0 || (*node)->e_state == 1))
				a = 1;
			str = ft_my_strjoin(str, (*node)->cmd);
		}
		(*node) = (*node)->next;
	}
	append_file(file, str, a);
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void	ft_output(t_datatoken **node, t_parce_node **parce, t_file **file)
{
	char	*str;
	int		a;

	str = NULL;
	a = 0;
	(*node) = (*node)->next;
	while ((*node))
	{
		if (ft_break(node))
			break ;
		else
		{
			if (*node && ((*node)->e_state == 0 || (*node)->e_state == 1))
				a = 1;
			str = ft_my_strjoin(str, (*node)->cmd);
		}
		(*node) = (*node)->next;
	}
	output_file(file, str, a);
	(*parce)->file = *file;
	if (!*node)
		(*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}
