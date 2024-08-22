#include "../minishell.h"

void process_quotes(char *str);

void process_quotes(char *str)
{
    int i = -1;
    int j = 0;
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;

    while (str[++i])
    {
        if (str[i] == '\'')
        {
            if (inside_double_quotes)
                str[j++] = str[i];
            else if (inside_single_quotes)
                inside_single_quotes = 0;
            else
                inside_single_quotes = 1;
        }
        else if (str[i] == '\"')
        {
            if (inside_single_quotes)
                str[j++] = str[i];
            else if (inside_double_quotes)
                inside_double_quotes = 0;
            else
                inside_double_quotes = 1;
        }
        else
            str[j++] = str[i];
    }
    str[j] = '\0';
}

void rem_double_quotes(t_parce_node **node)
{
    int i;
    t_parce_node *data;

    data = (*node);
    while (data)
    {
        i = 0;
        while (data->args && data->args[i])
        {
            process_quotes(data->args[i]);
            i++;
        }
        data = data->next;
    }
}
