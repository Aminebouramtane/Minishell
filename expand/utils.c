#include "../minishell.h"

void	ft_expand_dolar_single_char(Datatoken *node)
{
	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
		node->cmd = "$";
}

void	ft_expand_dolar_two_chars(Datatoken *node)
{
	char	*str;
	char	*env;
	char	*tmp;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 2)
	{
		tmp = node->cmd;
		node->cmd += 1;
		str = node->cmd;
		env = getenv("_");
		if (str[0] == '_' || str[0] == '?')
		{
			if (str[0] == '_')
				node->cmd = my_strdup_two(env);
			else if (str[0] == '?')
				node->cmd = ft_itoa(envi->exit_status);
			else
				node->cmd = "\0";
		}
		else
			node->cmd = tmp;
	}
}

void	ft_handle_special_case(Datatoken *node)
{
	if (node->cmd && node->cmd[0] && node->cmd[0] == '$'
		&& ft_strlen(node->cmd) == 1 && node->next && node->next->cmd
		&& (node->next->cmd[0] == '\'' || node->next->cmd[0] == '\"'))
	{
		node->cmd = "\0";
	}
}
