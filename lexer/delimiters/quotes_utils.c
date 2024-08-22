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
		if (str[end] == '\'' || str[end + 1] == '\"')
		{
			end++;
			break ;
		}
		end++;
	}
	tmp = my_strdup(str + start, end - start);
	if (data->flag)
		node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(tmp, 's', IN_COTE);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = end;
}