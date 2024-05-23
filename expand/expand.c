

#include "../minishell.h"

void	ft_expand_dolar(Datatoken *lst)
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

void	ft_expand_home(Datatoken *lst)
{
	Datatoken	*node;
	char		*tmp;
	char		*str;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->cmd[0] == '~')
		{
			node->cmd++;

			str = node->cmd;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, str);
			if (tmp)
				node->cmd = tmp;
			else
				node->cmd--;
		}
		node = node->next;
	}
}