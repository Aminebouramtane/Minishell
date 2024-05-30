

#include "../minishell.h"

char	*ft_my_strjoin(char const *s1, char const *s2);

void    ft_input(Datatoken **node, t_parce_node **parce, t_file **file)
{
    char    *str;

    str = NULL;
    (*node) = (*node)->next;
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->cmd[0] == ' ' && (*node)->type == 'w' && (*node)->state == 2)
        || (*node)->type == '|')
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 1, 0));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, "\"\'\t ");
}

void    ft_append(Datatoken **node, t_parce_node **parce, t_file **file)
{
    char    *str;

    str = NULL;
    (*node) = (*node)->next;
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->cmd[0] == ' ' && (*node)->type == 'w' && (*node)->state == 2)
        || (*node)->type == '|')
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_append_lstnew(str, 1));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, "\"\'\t ");
}

void    ft_output(Datatoken **node, t_parce_node **parce, t_file **file)
{
    char	*str;

	str = NULL;
    (*node) = (*node)->next;
    while ((*node))
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->cmd[0] == ' ' && (*node)->type == 'w' && (*node)->state == 2)
        || (*node)->type == '|')
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 0, 1));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, "\"\'\t ");
}

void    ft_cmd(Datatoken **node, t_parce_node **parce)
{
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || (*node)->type == '|')
            break ;
        else
            (*parce)->cmd = ft_my_strjoin((*parce)->cmd, (*node)->cmd);
        (*node) = (*node)->next;
    }
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, "\"\'\t ");
}

void    ft_heredoc(Datatoken **node, t_parce_node **parce, t_file **file, int *flag)
{
    char	*str;

	str = NULL;
    (*node) = (*node)->next;
    while ((*node))
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || (*node)->cmd[0] == '|')
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_heredoc_lstnew(1, str, *flag));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, "\"\'\t ");
}

void    ft_parce(t_parce_node **parce, t_vars *data)
{
    Datatoken       *node;
	t_parce_node	*parce_node;
    t_file          *file;
    int             flag;

    node = data->ndata;
    file = NULL;
    *parce = ft_parce_lstnew(NULL, file);
    parce_node = *parce;
    flag = -1;
    while (node)
    {
        if (node->cmd[0] == '<' && node->type == '<' && node->state == 2)
            ft_input(&node, &parce_node, &file);
        else if (node->cmd[0] == '>' && node->type == 'a' && node->state == 2)
            ft_append(&node, &parce_node, &file);
        else if (node->cmd[0] == '>' && node->type == '>' && node->state == 2)
            ft_output(&node, &parce_node, &file);
        else if (node->cmd[0] == '<' && node->type == 'h' && node->state == 2)
        {
            flag++;
            ft_heredoc(&node, &parce_node, &file, &flag);
        }
        else if ((node->cmd[0] == '|' && node->type == '|'))
        {
			ft_parce_lstadd_back(parce, ft_parce_lstnew(NULL, NULL));
            file = NULL;
            flag = -1;
            parce_node = parce_node->next;
            node = node->next;
		}
        else
            ft_cmd(&node, &parce_node);
    }
}

char	*ft_my_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ptr;
	int		len;

	i = 0;
	j = 0;
	if (!s1)
    {
        len = ft_strlen(s2);
        ptr = (char *)malloc(sizeof(char) * (len + 1));
        if (ptr == NULL)
            return (NULL);
        while (s2[j])
        {
            ptr[i + j] = s2[j];
            j++;
        }
        ptr[j] = '\0';
        return (ptr);
    }
    else 
    {
        len = ft_strlen(s1) + ft_strlen(s2);
        ptr = (char *)malloc(sizeof(char) * (len + 1));
        if (ptr == NULL)
            return (NULL);
        while (s1[i])
        {
            ptr[i] = s1[i];
            i++;
        }
        while (s2[j])
        {
            ptr[i + j] = s2[j];
            j++;
        }
        ptr[i + j] = '\0';
        return (ptr);
    }
    return (NULL);
}
