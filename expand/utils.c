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
		if (ft_isdigit(node->cmd[1]))
		{
			node->cmd = "\0";
			return ;
		}
		tmp = node->cmd;
		node->cmd += 1;
		str = node->cmd;
		env = getenv(str);
		if (env || str[0] == '?')
		{
			if (str[0] == '?')
				node->cmd = ft_itoa(envi->exit_status);
			else
				node->cmd = my_strdup_two(env);
		}
		else
			node->cmd = tmp;
	}
}
