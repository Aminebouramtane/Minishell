

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
		if (node->cmd[0] == '~' && node->state == 2)
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

// void	ft_remove_dqoutes(Datatoken *lst)
// {
// 	Datatoken	*node;

// 	node = lst;
// 	while (node)
// 	{
// 		if (node->cmd[0] == '\"')
// 			node->prev->next = node->next;
// 		node = node->next;
// 	}
// }


void	ft_remove_dqoutes(Datatoken **lst)
{
	Datatoken	*node;
	Datatoken	*temp;


	node = *lst;
	while (node)
	{
		if (node->cmd[0] == '\"')
		{
			node->cmd++;
			if (node->prev)
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			if (node == *lst)
				*lst = node->next;
			temp = node;
			node = node->next;
		}
		else
			node = node->next;
	}
}



void	ft_remove_qoutes(Datatoken *lst)
{
	Datatoken	*node;
	char		*str;
	int			i;

	node = lst;
	i = 0;
	str = NULL;
	while (node)
	{
		if (node->cmd[0] == '\'' && node->state == 0)
		{
			node->cmd++;
			while (node->cmd[i] != '\'')
				i++;
			str = my_strdup(node->cmd, i);
			node->cmd = str;
		}
		node = node->next;
	}
}

void	ft_expand(Datatoken *lst)
{
	ft_expand_dolar(lst);
	ft_expand_home(lst);
	ft_remove_qoutes(lst);
	// exit(1);
	ft_remove_dqoutes(&lst);
}