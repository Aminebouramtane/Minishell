#include "../minishell.h"

int	ft_syntax_lstsize(Datatoken *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

Datatoken *initialize_node(Datatoken *data, int *len)
{
    *len = ft_syntax_lstsize(data);
    return data;
}