#include "../minishell.h"

void handle_redirection(Datatoken **node, t_parce_node **parce_node, t_file **file)
{
	if (*node && (*node)->cmd[0] && (*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
		ft_input(node, parce_node, file);
	else if (*node && (*node)->cmd[0] && (*node)->cmd[0] == '>' && (*node)->type == 'a' && (*node)->state == 2)
		ft_append(node, parce_node, file);
	else if (*node && (*node)->cmd[0] && (*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
		ft_output(node, parce_node, file);
	ft_cmd(node, parce_node);
}

void handle_special_cases(Datatoken **node, t_parce_node **parce_node, t_file **file, int *flag, t_parce_node **parce)
{
	if ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
	{
		(*flag)++;
		ft_heredoc(node, parce_node, file, flag);
	}
	else if ((*node)->cmd[0] == '|' && (*node)->type == '|' && (*node)->state == 2)
	{
		(*parce_node)->args = split_lexer((*parce_node)->cmd, " \t\n\r\f\v");
		(*parce_node)->first = my_strdup_two((*parce)->args[0]);
		ft_parce_lstadd_back(parce, ft_parce_lstnew(NULL, NULL));
		*file = NULL;
		*parce_node = (*parce_node)->next;
		*node = (*node)->next;
	}
}

void ft_parce(t_parce_node **parce, t_vars *data)
{
	Datatoken *node;
	t_parce_node *parce_node;
	t_file *file;
	int flag;

    node = data->ndata;
    file = NULL;
    flag = -1;
	*parce = ft_parce_lstnew(NULL, file);
	parce_node = *parce;
	while (node)
	{
		handle_special_cases(&node, &parce_node, &file, &flag, parce);
		handle_redirection(&node, &parce_node, &file);
		if (!node || node->cmd[0] == '|' || node->cmd[0] == '<' || node->cmd[0] == '>')
			continue;
		node = node->next;
	}
}


char	*ft_my_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	len;

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
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}
