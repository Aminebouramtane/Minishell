
#include "../../minishell.h"

void	fill_input_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	size_t			a;

	a = *i;
	if (str[a + 1] == '<')
	{
		if (data->flag)
			node = ft_my_lstnew("<<", 'h', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew("<<", 'h', GENERAL);
		a = a + 2;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew("<", '<', IN_DOUBLE_COTE);
		else
		{
			node = ft_my_lstnew("<", '<', GENERAL);
		}
		a++;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	ft_my_lstadd_back(&(data->ndata), node);
}

void	fill_output_in_node(char *str, size_t *i, t_vars *data)
{
	Datatoken	*node;
	size_t			a;

	a = *i;
	if (str[a + 1] == '>')
	{
		if (data->flag)
			node = ft_my_lstnew(">>", 'a', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew(">>", 'a', GENERAL);
		a = a + 2;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	else
	{
		if (data->flag)
			node = ft_my_lstnew(">", '>', IN_DOUBLE_COTE);
		else
			node = ft_my_lstnew(">", '>', GENERAL);
		a++;
		while ((str[a] == ' ' || str[a] == '\t') && !data->flag)
			a++;
		*i = a;
	}
	ft_my_lstadd_back(&(data->ndata), node);
}