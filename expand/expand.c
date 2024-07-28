

#include "../minishell.h"

void	ft_expand_dolar(Datatoken *lst)
{
	Datatoken	*node;
	char		*str;
	char		*tmp;
	char		*env;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		if (node->cmd && node->cmd[0] && node->cmd[0] == '$' && ft_strlen(node->cmd) == 1 && node->next && node->next->cmd 
		&& (node->next->cmd[0] == '\'' || node->next->cmd[0] == '\"'))
		{
			tmp = "\0";
			node->cmd = tmp;
		}
		if (node->cmd && node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
		{
			node->cmd = "$";
		}
		else if (node->cmd && node->cmd[0] == '$' && ft_strlen(node->cmd) > 2)
		{
			node->cmd = node->cmd + 1;
			str = node->cmd;
			env = getenv(str);
			tmp = my_strdup_two(env);
			if (tmp)
				node->cmd = tmp;
		}
		else if (node->cmd && node->cmd[0] == '$' && ft_strlen(node->cmd) == 2)
		{
			node->cmd = node->cmd + 1;
			str = node->cmd;
			env = getenv("_");
			if (str[0] == '_')
			{
				tmp = my_strdup_two(env);
				if (tmp)
					node->cmd = tmp;
			}
			else
			{
				tmp = "\0";
				node->cmd = tmp;
			}
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
		if (node->cmd[0] == '~' && node->state == 2)
		{
			node->cmd = node->cmd + 1;

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

void	ft_expand(Datatoken *lst)
{
	ft_expand_dolar(lst);
	ft_expand_home(lst);

}