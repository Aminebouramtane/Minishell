#include "../minishell.h"

int handle_echo_command(Datatoken **node)
{
    if (*node && (*node)->next && (ft_strncmp((*node)->cmd, "echo") == 0))
    {
        *node = (*node)->next;
        while (*node && (*node)->cmd[0] == ' ' && (*node)->state == 2)
            *node = (*node)->next;
        if (!(*node))
            return 0;
        if ((*node)->cmd[0] == '>' || (*node)->cmd[0] == '<'
            || ((*node)->cmd[0] == '<' && (*node)->type == 'h')
            || ((*node)->cmd[0] == '>' && (*node)->type == 'a'))
        {
            if (!(*node)->next)
            {
                ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
                return 1;
            }
        }
    }
    return 0;
}

int handle_pipe_command(Datatoken *node, int len)
{
    if (node && node->cmd[0] == '|' && node->state == 2 && len == 1)
    {
        ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
        return 1;
    }
    return 0;
}

int handle_subsequent_pipe_redirect(Datatoken **node)
{
    if (*node && (*node)->next && (*node)->cmd[0] == '|' && (*node)->state == 2)
    {
        *node = (*node)->next;
        while ((*node)->cmd[0] == ' ' && (*node)->state == 2)
            *node = (*node)->next;
        if (!(*node))
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            return 1;
        }
        if ((*node)->cmd[0] == '|' && (*node)->state == 2)
        {
            ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
            return 1;
        }
        if ((*node)->cmd[0] == '>' && (*node)->state == 2 && !(*node)->next)
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            return 1;
        }
    }
    return 0;
}


int handle_final_redirect(Datatoken *node)
{
    if (node && !node->next && ((node->cmd[0] == '>' && node->state == 2)
        || (node->cmd[0] == '<' && node->state == 2)))
    {
        ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
        return 1;
    }
    if (node && node->next && ((node->cmd[0] == '>' && node->state == 2)
        || (node->cmd[0] == '<' && node->state == 2)))
    {
        node = node->next;
        while (node->cmd[0] == ' ' && node->state == 2)
            node = node->next;
        if (!node)
            return 0;
        if (node->cmd[0] == '|' && node->state == 2)
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            return 1;
        }
    }
    return 0;
}

int syntax_err(Datatoken *data)
{
    Datatoken *node;
    int len;

    node = initialize_node(data, &len);
    while (node)
    {
        if (handle_echo_command(&node))
            return 1;
        if (handle_pipe_command(node, len))
            return 1;
        if (handle_subsequent_pipe_redirect(&node))
            return 1;
        if (handle_final_redirect(node))
            return 1;
        node = node->next;
    }
    return 0;
}
