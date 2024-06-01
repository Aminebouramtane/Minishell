

#include "../minishell.h"

void util_q(char *str);
void util_dq(char *str);

void fn_rm_dq(char *str)
{
    int i;
	int j;
	int f;

	i = 0;
	j = 0;
	f = 0;
    // if (!str)
    //     return ;
	f++;
	while (str[f] != '\"')
    	f++;
	f--;
    while (str[i])
	{
        if (str[i] != '"')
            str[j++] = str[i];
        i++;
    }
	if (str[f] == '\'')
		util_q(str + f);
    str[j] = '\0';
}

void fn_rm_sq(char *str)
{
    int i; 
	int j;
	int f;

	i = 0;
	j = 0;
	f = 0;
    // if (!str)
    //     return;
	f++;
		while (str[f] != '\'')
        	f++;
	f--;
    while (str[i])
	{
        if (str[i] != '\'')
            str[j++] = str[i];
        i++;
    }
	if (str[f] == '\"')
		util_dq(str + f);
    str[j] = '\0';
}

void util_q(char *str)
{
    int i; 
	int j;

	i = 0;
	j = 0;
    if (!str)
        return;
    while (str[i])
	{
        if (str[i] != '\'')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}

void util_dq(char *str)
{
    int i; 
	int j;

	i = 0;
	j = 0;
    if (!str)
        return;
    while (str[i])
	{
        if (str[i] != '\"')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}


void	rem_double_quotes(t_parce_node **node)
{
	int		i;

	while ((*node))
	{
		i = 0;
		while ((*node)->args && (*node)->args[i])
		{
			if ((*node)->args[i][0] == '\"')
				fn_rm_dq((*node)->args[i]);
			else if ((*node)->args[i][0] == '\'')
				fn_rm_sq((*node)->args[i]);
			i++;
		}
		if (!(*node)->next)
			break;
		(*node) = (*node)->next;
	}
}

