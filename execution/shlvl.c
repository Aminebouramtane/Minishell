#include "../minishell.h"

void	handle_shlvl(void)
{
	t_env	*temp;
	char	*value;
	int		shlvl;

	value = get_value("SHLVL");
	temp = envi;
	while (temp && ft_strncmp(temp->key, "SHLVL") != 0)
		temp = temp->next;
	if (value != NULL)
	{
		shlvl = ft_atoi(temp->value) + 1;
		temp->value = ft_itoa(shlvl);
	}
	else
	{
		temp->value = ft_itoa(1);
	}
}
