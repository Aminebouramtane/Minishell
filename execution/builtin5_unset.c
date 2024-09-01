#include "../minishell.h"

void	ft_unset_a_node(t_env *temp)
{
	if (!temp)
		return ;
  	if (temp->prev)
		temp->prev->next = temp->next;
  	else
		envi = temp->next;
	if (temp->next)
  		temp->next->prev = temp->prev;
	ft_env_delone(temp);
}

void	ft_unset(t_parce_node *parce)
{
	int		i;
	t_env	*temp;

	i = 1;
	temp = envi;
	while (parce->args[i])
	{
		if (!parce || !parce->args || !parce->args[i])
			return ;
		while (temp && temp->key 
		&& ft_strncmp(parce->args[i], temp->key) != 0)
        temp = temp->next;
		ft_unset_a_node(temp);
		i++;
		temp = envi;
	}
	envi->exit_status = 0;
}
