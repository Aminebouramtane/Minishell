
#include "../../minishell.h"

void	fill_input_in_node(char *str, int *i, t_vars *data)
{
	Datatoken	*node;

	if (str[*i + 1] == '<')
	{
		if (data->flag)
			node = ft_my_lstnew("<<", 'h', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<<", 'h', GENERAL);
		*i = *i + 1;
	}
	else
	{		
		if (data->flag)
			node = ft_my_lstnew("<", '<', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<", '<', GENERAL);
	}
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}

void	fill_output_in_node(int *i, t_vars *data)
{
	Datatoken	*node;

	if (data->flag)
		node = ft_my_lstnew(">", '>', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(">", '>', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
	*i = *i + 1;
}