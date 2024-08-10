#include "../minishell.h"

void	ft_unset(t_parce_node *parce)
{
	t_env	*temp;

	temp = envi;
	if (!parce || !parce->args || !parce->args[1])
		return ;
	while (temp && temp->env_var
		&& ft_strncmp(parce->args[1], temp->env_var) != 0)
		temp = temp->next;
	if (!temp)
		return ;
	if (temp->prev == NULL)
	{
		envi = envi->next;
	}
	else
	{
		temp->prev->next = temp->next;
	}
	ft_env_delone(temp);
}
