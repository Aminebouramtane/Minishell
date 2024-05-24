
#include "../../minishell.h"

void	fill_pipe_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("|", '|', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("|", '|', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}