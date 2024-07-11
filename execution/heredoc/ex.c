#include "../../minishell.h"

void	ft_heredoc_expand_dolar(t_heredoc *lst)
{
	t_heredoc	*node;
	char		*str;
	char		*tmp;
	char		*env;

	if (!lst)
		return ;
	node = lst;
	while (node)
	{
		if (node->input && node->input[0] == '$' && ft_strlen(node->input) > 2)
		{
			node->input++;
			str = node->input;
			env = getenv(str);
			tmp = my_strdup_two(env);
			if (tmp)
				node->input = tmp;
			else
				node->input--;
		}
		else if (node->input && node->input[0] == '$' && ft_strlen(node->input) == 2)
		{
			node->input++;
			str = node->input;
			env = getenv("_");
			tmp = my_strdup_two(env);
			if (tmp)
				node->input = tmp;
			else
				node->input--;
		}
		node = node->next;
	}
}

void	ft_heredoc_expand_home(t_heredoc *lst)
{
	t_heredoc	*node;
	char		*tmp;
	char		*str;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->input[0] == '~')
		{
			node->input++;

			str = node->input;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, str);
			if (tmp)
				node->input = tmp;
			else
				node->input--;
		}
		node = node->next;
	}
}

void	ft_heredoc_expand(t_heredoc *lst)
{
	ft_heredoc_expand_dolar(lst);
	ft_heredoc_expand_home(lst);
}