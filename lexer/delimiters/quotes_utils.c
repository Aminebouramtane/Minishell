#include "../../minishell.h"

static void process_quotes(char *str, size_t *i, t_vars *data)
{

    if (str[*i] == '\'')
    {
        if (data->flag == 0)
        {
            data->flag = 1;
        }
        else if(data->flag == 1)
        {
            data->flag = 0;
        }
        (*i)++;
    }
}

void	fill_qoute_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	size_t			start;
	size_t			end;

	start = *i;
	end = *i;
	process_quotes(str + end, i, data);
	while (str[end])
	{
		end++;
		if (str[end] == '\'')
		{
			end++;
			break ;
		}
	}
	tmp = my_strdup(str + start, end - start);
	if (data->flag)
		node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(tmp, 's', IN_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = end;
}