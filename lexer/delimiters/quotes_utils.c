#include "../../minishell.h"

void	fill_qoute_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	char		*tmp;
	size_t			start;
	size_t			end;

	start = *i;
	end = *i;
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
	if (!check_quotes(tmp) || data->f_qoute == 1)
	{
		node = ft_my_lstnew("'", 's', IN_DOUBLE_COTE);
		ft_my_lstadd_back(&(data->ndata), node);
		*i += 1;
		return ;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew(tmp, 's', IN_COTE);
	}
	ft_my_lstadd_back(&(data->ndata), node);
	*i = end;
}