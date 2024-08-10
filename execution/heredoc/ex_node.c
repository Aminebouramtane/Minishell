#include "../../minishell.h"

void	fill_env_in_heredoc(char *str, t_heredoc **here, size_t *i, char *del)
{
	t_heredoc		*node;
	char			*tmp;
	size_t			start;
	size_t			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (in_delimiters(str[end], del))
			break ;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_heredoc_lstnew(tmp);
	ft_heredoc_lstadd_back(here, node);
}

void	fill_in_heredoc(char *str, t_heredoc **here, size_t *i, char *del)
{
	t_heredoc		*node;
	char			*tmp;
	size_t			start;
	size_t			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (in_delimiters(str[end], del))
			break ;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	node = ft_heredoc_lstnew(tmp);
	ft_heredoc_lstadd_back(here, node);
}

char	*expande_heredoc(char *str)
{
	size_t			i;
	t_heredoc		*here;
	char			*res;

	i = 0;
	here = NULL;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			fill_env_in_heredoc(str, &here, &i, "|<>$+-/%%#@!* \t\'\"");
		else
			fill_in_heredoc(str, &here, &i, "$");
	}
	ft_heredoc_expand(here);
	while (here)
	{
		res = ft_my_strjoin(res, here->input);
		here = here->next;
	}
	return (res);
}
