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
		if (node->input && node->input[0] && node->input[0] == '$' && ft_strlen(node->input) == 1)
		{
			if (node->next && node->next->input && 
			   (node->next->input[0] == '\'' || node->next->input[0] == '\"'))
			{
				tmp = "\0";
				node->input = tmp;
			}
		}
		else if (node->input && node->input[0] == '$' && ft_strlen(node->input) > 1)
		{
			str = node->input + 1;
			env = getenv(str);
			tmp = my_strdup_two(env);
			if (tmp)
				node->input = tmp;
		}
		else if (node->input && node->input[0] == '$' && ft_strlen(node->input) == 2)
		{
			str = node->input + 1;
			env = getenv("_");
			if (str && str[0] == '_')
			{
				tmp = my_strdup_two(env);
				if (tmp)
					node->input = tmp;
			}
			else
			{
				tmp = "\0";
				node->input = tmp;
			}
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
		if (node->input && node->input[0] == '~')
		{
			str = node->input + 1;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, str);
			if (tmp)
				node->input = tmp;
		}
		node = node->next;
	}
}

void	ft_heredoc_expand(t_heredoc *lst)
{
	ft_heredoc_expand_dolar(lst);
	ft_heredoc_expand_home(lst);
}
