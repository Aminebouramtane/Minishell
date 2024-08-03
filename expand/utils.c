#include "../minishell.h"

void	ft_expand_dolar_single_char(Datatoken *node)
{
	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 1)
		node->cmd = "$";
}

void	ft_expand_dolar_two_chars(Datatoken *node)
{
	char	*str;
	char	*tmp;
	char	*env;

	if (node->cmd[0] == '$' && ft_strlen(node->cmd) == 2)
	{
		node->cmd += 1;
		str = node->cmd;
		env = getenv("_");
		if (str[0] == '_')
		{
			tmp = my_strdup_two(env);
			if (tmp)
			{
				free(node->cmd - 1);
				node->cmd = tmp;
			}
		}
		else
		{
			tmp = "\0";
			node->cmd = tmp;
		}
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
