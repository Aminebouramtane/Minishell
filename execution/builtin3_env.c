#include "../minishell.h"


t_env	*get_env_vars(char **env_vars)
{
	t_env	*temp;
	char **variable;
	int i;

	i = 0;
	variable = NULL;
	while (env_vars && env_vars[i])
		ft_env_lstadd_back(&envi, ft_env_lstnew(env_vars[i++]));
	temp = envi;
	i = 0;
	while (temp && temp->env_var)
	{
		variable = ft_split(temp->env_var, '=');	
		temp->key = ft_strdup(variable[0]);
		temp->value = getenv(variable[0]);
		//printf("%s\n", temp->key);
		//printf("%s\n", temp->value);
		ft_free(variable);
		variable = NULL;
		temp = temp->next;
	}
	return (envi);
}

void	ft_env()
{
	t_env	*temp;

	temp = envi;
	while (temp)
	{
		if (temp->value != NULL)
		{
			ft_putstr_fd(temp->env_var, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}
