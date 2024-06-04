#include "../minishell.h"

void	ft_unset(t_parce_node *parce, t_env *envi)
{
	t_env *temp;

	temp = envi;
	if (!parce || !parce->args || !parce->args[1])
		return ;
	while (temp && temp->env_var && ft_strncmp(parce->args[1], temp->env_var, ft_strlen(parce->args[1])) != 0)
		temp = temp->next;
	if (temp && !temp->prev) // this is for $HOME(or first key)
		envi = envi->next;
	else if (temp)
		temp->prev->next = temp->next;
	ft_env_delone(temp);
}