

#include "../minishell.h"

int     syntax_err(Datatoken *data)
{
    Datatoken    *node;
    int           len;

    node = data;
    len = ft_syntax_lstsize(node);
    while (node)
    {
//------------------------------------redirection after echo----------------------------------
        if (node && node->next && (ft_strncmp(node->cmd, "echo") == 0))
        {
            node = node->next;
            while (node && node->cmd[0] == ' ' && node->state == 2)
                node = node->next;
            if (!node)
                break;
            if ((node->cmd[0] == '>' || node->cmd[0] == '<'
            || (node->cmd[0] == '<' && node->type == 'h')
            || (node->cmd[0] == '>' && node->type == 'a')))
            {
                if (!node->next)
                {
                    ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
                    return (1);
                }
            }
        }
//--------------------------------------pipe after pipe----------------------------------------
//------------------------------------redirection after pipe-----------------------------------
        if (node && node->cmd[0] == '|' && node->state == 2 && len == 1)
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
            return (1);
        }
        else if (node && node->next && node->cmd[0] == '|' && node->state == 2)
        {
            node = node->next;
            while (node->cmd[0] == ' ' && node->state == 2)
                node = node->next;
            if (!node)
            {
                ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
                return (1);
            }
            if (node->cmd[0] == '|' && node->state == 2)
            {
                ft_putstr_fd("syntax error near unexpected token `||'\n", 1);
                return (1);
            }
            if ((node->cmd[0] == '>' && node->state == 2)
            || (node->cmd[0] == '<' && node->state == 2))
            {
                ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
                return (1);
            }
        }
//-----------------------------------pipe after redirection------------------------------------
        if (node && !node->next && ((node->cmd[0] == '>' && node->state == 2)
        || ( node->cmd[0] == '<' && node->state == 2)))
        {
            ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
            return (1);
        }
        if (node && node->next && ((node->cmd[0] == '>' && node->state == 2)
        || ( node->cmd[0] == '<' && node->state == 2)))
        {
            node = node->next;
            while (node->cmd[0] == ' ' && node->state == 2)
                node = node->next;
            if (!node)
                break ;
                
            if ((node->cmd[0] == '|' && node->state == 2)
            ||(node->cmd[0] == '>' && node->state == 2)
            || (node->cmd[0] == '<' && node->state == 2))
            {
                ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
                return (1);
            }
        }
//----------------------------------------------------------------------------------------------
        node = node->next;
    }
    return (0);
}