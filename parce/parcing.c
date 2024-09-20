/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:11:15 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/19 13:24:50 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(t_datatoken **node,
	t_parce_node **parce_node, t_file **file)
{
	if (*node && (*node)->cmd && (*node)->cmd[0] && (*node)->cmd[0] == '<'
		&& (*node)->e_type == '<' && (*node)->e_state == 2)
		ft_input(node, parce_node, file);
	else if (*node && (*node)->cmd && (*node)->cmd[0] && (*node)->cmd[0] == '>'
		&& (*node)->e_type == 'a' && (*node)->e_state == 2)
		ft_append(node, parce_node, file);
	else if (*node && (*node)->cmd && (*node)->cmd[0] && (*node)->cmd[0] == '>'
		&& (*node)->e_type == '>' && (*node)->e_state == 2)
		ft_output(node, parce_node, file);
	ft_cmd(node, parce_node);
}

void	handle_special_cases(t_datatoken **node,
			t_special_cases *cases, int *flag)
{
	if (*node && (*node)->cmd && (*node)->cmd[0] == '<'
		&& (*node)->e_type == 'h' && (*node)->e_state == 2)
	{
		(*flag)++;
		ft_heredoc(node, cases->parce_node, cases->file, flag);
	}
	else if ((*node)->e_type == '|' && (*node)->e_state == 2)
	{
		(*cases->parce_node)->args = split_lexer((\
*cases->parce_node)->cmd, " \t\n\r\f\v");
		if (cases && (*cases->parce) && (*cases->parce)->args
			&& (*cases->parce)->args[0])
			(*cases->parce_node)->first = \
my_strdup_two((*cases->parce)->args[0]);
		ft_parce_lstadd_back(cases->parce, ft_parce_lstnew(NULL, NULL));
		*cases->file = NULL;
		*cases->parce_node = (*cases->parce_node)->next;
		*node = (*node)->next;
	}
}

void	ft_parce(t_parce_node **parce, t_vars *data)
{
	t_datatoken		*node;
	t_parce_node	*parce_node;
	t_file			*file;
	t_special_cases	cases;

	node = data->ndata;
	file = NULL;
	*parce = ft_parce_lstnew(NULL, file);
	parce_node = *parce;
	cases.parce_node = &parce_node;
	cases.file = &file;
	cases.parce = parce;
	cases.flag = 0;
	while (node)
	{
		handle_special_cases(&node, &cases, &(cases.flag));
		handle_redirection(&node, &parce_node, &file);
		if (!node || node->cmd[0] == '|' || node->cmd[0] == '<'
			|| node->cmd[0] == '>')
			continue ;
		node = node->next;
	}
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	len;

	int (i), (j);
	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_malloc(sizeof(char) * (len + 1), 0);
	if (!ptr)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			ptr[i] = s1[i];
	else
		i = 0;
	j = 0;
	while (s2 && s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}
