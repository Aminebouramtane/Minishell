/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:01:13 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/08 20:50:53 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_file	*ft_file_heredoc_lstnew(char *name, int is_quoted, char *eof, int index)
{
	t_file	*my_node;

	my_node = (t_file *)ft_malloc(sizeof(t_file), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->file = name;
	my_node->redir_in = 0;
	my_node->redir_out = 0;
	my_node->heredoc = 1;
	my_node->is_quoted = is_quoted;
	my_node->append = 0;
	my_node->eof = eof;
	my_node->index = index;
	my_node->next = NULL;
	my_node->prev = NULL;
	return (my_node);
}

t_file	*ft_file_heredoc_lstlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_file_heredoc_lstadd_back(t_file **lst, t_file *new)
{
	t_file	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

int	ft_break(t_datatoken **node)
{
	return (((*node)->e_type == '<' && (*node)->e_state == 2)
		|| ((*node)->e_type == '>' && (*node)->e_state == 2)
		|| ((*node)->e_type == 'h' && (*node)->e_state == 2)
		|| ((*node)->e_type == 'w' && (*node)->e_state == 2)
		|| ((*node)->e_type == '|' && (*node)->e_state == 2));
}

void	append_file(t_file **file, char *str, int a)
{
	process_quotes(str);
	if (a == 1)
		ft_file_lstadd_back(file, ft_file_append_lstnew(str, 1, 1));
	else
		ft_file_lstadd_back(file, ft_file_append_lstnew(str, 1, 0));
}
