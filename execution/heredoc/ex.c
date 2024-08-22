#include "../../minishell.h"

static void	ft_expand_h_dolar_single_char(t_heredoc *node)
{
	if (node->input[0] == '$' && ft_strlen(node->input) == 1)
		node->input = "$";
}

static void	ft_expand_h_dolar_two_chars(t_heredoc *node)
{
	char	*str;
	char	*env;
	char	*tmp;

	if (node->input[0] == '$' && ft_strlen(node->input) == 2)
	{
		tmp = node->input;
		node->input += 1;
		str = node->input;
		env = getenv("_");
		if (str[0] == '_' || str[0] == '?')
		{
			if (str[0] == '_')
				node->input = my_strdup_two(env);
			else if (str[0] == '?')
				node->input = ft_itoa(envi->exit_status);
			else
				node->input = "\0";
		}
		else
			node->input = tmp;
	}
}

static void	ft_handle_h_special_case(t_heredoc *node)
{
	if (node->input && node->input[0] && node->input[0] == '$'
		&& ft_strlen(node->input) == 1 && node->next && node->next->input
		&& (node->next->input[0] == '\'' || node->next->input[0] == '\"'))
	{
		node->input = "\0";
	}
}

static void	ft_expand_h_dolar_long(t_heredoc *node)
{
	char	*str;
	char	*tmp;
	char	*env;

	if (node->input[0] == '$' && ft_strlen(node->input) > 2)
	{
		if (ft_isdigit(node->input[1]))
		{
			node->input = node->input + 2;
			return ;
		}
		node->input += 1;
		str = node->input;
		env = getenv(str);
		tmp = my_strdup_two(env);
		if (tmp)
			node->input = tmp;
		else
			node->input = "\0";
	}
}

static void	ft_expand_h_dolar_single(t_heredoc *node)
{
	ft_expand_h_dolar_single_char(node);
	ft_expand_h_dolar_long(node);
	ft_expand_h_dolar_two_chars(node);
}

static void	ft_heredoc_expand_dolar(t_heredoc *lst)
{
	t_heredoc	*node;

	node = lst;
	while (node)
	{
		ft_handle_h_special_case(node);
		if (node->input && node->input[0] == '$')
		{
			ft_expand_h_dolar_single(node);
		}
		node = node->next;
	}
}

static void	ft_heredoc_expand_home(t_heredoc *lst)
{
	t_heredoc	*node;
	char		*tmp;
	char		*env;

	node = lst;
	while (node)
	{
		if (node->input[0] == '~')
		{
			node->input += 1;
			env = my_strdup_two(getenv("HOME"));
			tmp = ft_strjoin(env, node->input);
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
