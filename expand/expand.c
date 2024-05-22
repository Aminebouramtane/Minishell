

#include "../minishell.h"

void	ft_expand(Datatoken *lst)
{
	Datatoken	*node;
	char		*str;
	char		*tmp;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->cmd[0] == '$')
		{
			node->cmd++;
			str = node->cmd;
			env = getenv(str);
			tmp = my_strdup_two(env);
			if (tmp)
				node->cmd = tmp;
			else
				node->cmd--;
		}
		node = node->next;
	}
}