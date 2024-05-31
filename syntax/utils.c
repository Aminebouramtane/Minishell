

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