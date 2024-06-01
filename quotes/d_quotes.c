

#include "../minishell.h"

void fn_rm_dq(char *str)
{
    int i;
	int j;

	i = 0;
	j = 0;
    if (!str)
        return;
    while (str[i])
	{
        if (str[i] != '"')
            str[j++] = str[i];
        i++;
		// exit(1);
    }
    str[j] = '\0';
}

void fn_rm_sq(char *str)
{
    int i; 
	int j;

	i = 0;
	j = 0;
    if (!str)
        return;
    while (str[i])
	{
        if (str[i] != '"')
            str[j++] = str[i];
        i++;
		// exit(1);
    }
    str[j] = '\0';
}


void	rem_double_quotes(t_parce_node **node)
{
	int		i;

	while ((*node))
	{
		i = 0;
		while ((*node)->args[i])
		{
			if (in_delimiters('\"', (*node)->args[i]))
				fn_rm_dq((*node)->args[i]);
			else if (in_delimiters('\'', (*node)->args[i]))
				fn_rm_sq((*node)->args[i]);
			printf("----****************-------%s\n", (*node)->args[i]);
			i++;
		}
		if (!(*node)->next)
			break;
		(*node) = (*node)->next;
	}
}

