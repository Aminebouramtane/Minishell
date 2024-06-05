

#include "../minishell.h"


static  char *ft_remove_qoutes(char *lst)
{
	char		*str;
	int			i;

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

static void	ft_remove_dqoutes(Datatoken **lst)
{
	Datatoken	*node;
    int         flag;

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
        || ((*node)->type == '|' && (*node)->state == 2))
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 1, 0));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
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
        || ((*node)->type == '|' && (*node)->state == 2))
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_append_lstnew(str, 1));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
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
        || ((*node)->type == '|' && (*node)->state == 2))
            break;
        else
            str = ft_my_strjoin(str, (*node)->cmd);
        (*node) = (*node)->next;
    }
    ft_file_lstadd_back(file, ft_file_lstnew(str, 0, 1));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void    ft_cmd(Datatoken **node, t_parce_node **parce)
{
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->type == '|' && (*node)->state == 2))
            break ;
        else
            (*parce)->cmd = ft_my_strjoin((*parce)->cmd, (*node)->cmd);
        (*node) = (*node)->next;
    }
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v"); 
}

void    ft_heredoc(Datatoken **node, t_parce_node **parce, t_file **file, int *flag)
{
    char	*str;
    char    *name;
    size_t  a;

	str = NULL;
    a = 0;
    (*node) = (*node)->next;
    while ((*node))
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == 'a' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->cmd[0] == ' ' && (*node)->type == 'w' && (*node)->state == 2)
        || ((*node)->type == '|' && (*node)->state == 2))
            break;
        else
        {
            if (*node && ((*node)->state == 0 || (*node)->state == 1))
                a = 1;
            printf("$$$$$$$$$$$$$$$$$$$ %c\n", (*node)->cmd[0]);
            if ((*node)->cmd[0] == '\'' && (*node)->state == 0)
                str = ft_my_strjoin(str, ft_remove_qoutes((*node)->cmd));
            else if ((*node)->cmd[0] == '\"' && (*node)->state == 1)
                ft_remove_dqoutes(node);
            else
                str = ft_my_strjoin(str, (*node)->cmd);
        }
        (*node) = (*node)->next;
    }
    name = "./tmp/heredoc";
    if (a)
        ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 1, str, *flag));
    else
        ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 0, str, *flag));
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
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
        else if (node->cmd[0] == '|' && node->type == '|' && node->state == 2)
        {
            parce_node->args = split_lexer(parce_node->cmd, " \t\n\r\f\v");
			ft_parce_lstadd_back(parce, ft_parce_lstnew(NULL, NULL));
            file = NULL;
            parce_node = parce_node->next;
            node = node->next;
		}
        else
            ft_cmd(&node, &parce_node);
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
	ptr = (char *)malloc(sizeof(char) * (len + 1));
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
    free(s1);
    s1 = NULL;
	return (ptr);
}
