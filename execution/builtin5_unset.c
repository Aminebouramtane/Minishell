#include "../minishell.h"

//void	ft_unset(t_parce_node *parce)
//{
//	t_env	*temp;

//	temp = envi;
//	if (!parce || !parce->args || !parce->args[1])
//		return ;
//	while (temp && temp->env_var && temp->key
//		&& ft_strncmp(parce->args[1], temp->key) != 0)
//		temp = temp->next;
//	if (!temp)
//		return ;
//	if (temp->prev == NULL)
//	{
//		envi = envi->next;
//	}
//	else
//	{
//		temp->prev->next = temp->next;
//	}
//	ft_env_delone(temp);
//}

void	ft_unset(t_parce_node *parce)
{
    t_env	*temp;

    if (!parce || !parce->args || !parce->args[1])
        return ;
    temp = envi;
    while (temp && temp->key 
		&& ft_strncmp(parce->args[1], temp->key) != 0)
        temp = temp->next;
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
