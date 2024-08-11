#include "../minishell.h"

void    ft_cmd(Datatoken **node, t_parce_node **parce)
{
    while (*node)
    {
        if (((*node)->cmd[0] == '<' && (*node)->type == '<' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == '>' && (*node)->state == 2)
        || ((*node)->cmd[0] == '>' && (*node)->type == 'a' && (*node)->state == 2)
        || ((*node)->cmd[0] == '<' && (*node)->type == 'h' && (*node)->state == 2)
        || ((*node)->type == '|' && (*node)->state == 2))
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

void initialize_and_traverse_node(Datatoken **node, char **str, size_t *a)
{
    *str = NULL;
    *a = 0;
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
                *a = 1;
            if ((*node)->cmd[0] == '\'' && (*node)->state == 0)
                *str = ft_my_strjoin(*str, ft_remove_qoutes((*node)->cmd));
            else if ((*node)->cmd[0] == '\"' && (*node)->state == 1)
                ft_remove_dqoutes(node);
            else
                *str = ft_my_strjoin(*str, (*node)->cmd);
        }
        (*node) = (*node)->next;
    }
}

void handle_file(t_file **file, int *flag, char *str, size_t a)
{
    char *name = "./tmp/heredoc";
    
    if (a)
        ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 1, str, *flag));
    else
        ft_file_lstadd_back(file, ft_file_heredoc_lstnew(name, 0, str, *flag));
}

void final_updates(Datatoken **node, t_parce_node **parce, t_file **file)
{
    (*parce)->file = *file;
    if (!*node)
        (*parce)->args = split_lexer((*parce)->cmd, " \t\n\r\f\v");
}

void ft_heredoc(Datatoken **node, t_parce_node **parce, t_file **file, int *flag)
{
    char *str;
    size_t a;

    initialize_and_traverse_node(node, &str, &a);
    handle_file(file, flag, str, a);
    final_updates(node, parce, file);
}
