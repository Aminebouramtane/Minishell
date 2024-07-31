#include "../../minishell.h"

void	fill_open_in_node(size_t *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew("(", '(', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew("(", '(', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_close_in_node(size_t *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew(")", ')', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(")", ')', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}
