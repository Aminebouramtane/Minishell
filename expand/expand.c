#include "../minishell.h"

void	ft_expand_dolar_long(Datatoken *node)
{
	char	*str;
	char	*tmp;
	char	*env;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) > 2)
	{
		node->cmd += 1;
		str = node->cmd;
		env = getenv(str);
		tmp = my_strdup_two(env);
		if (tmp)
			node->cmd = tmp;
	}
}

void	ft_expand_dolar_single(Datatoken *node)
{
	ft_expand_dolar_single_char(node);
	ft_expand_dolar_long(node);
	ft_expand_dolar_two_chars(node);
}

void	ft_expand_dolar(Datatoken *lst)
{
	Datatoken	*node;

	node = lst;
	while (node)
	{
		ft_handle_special_case(node);
		if (node->cmd && node->cmd[0] == '$')
		{
			ft_expand_dolar_single(node);
		}
		node = node->next;
	}
}

void	ft_expand_home(Datatoken *lst)
{
	Datatoken	*node;
	char		*tmp;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->cmd[0] == '~' && node->state == 2)
		{
			node->cmd += 1;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, node->cmd);
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
