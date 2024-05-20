/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:44:06 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/20 11:03:01 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    in_delimiters(char a, char *delimiters)
{
    int     i;
    
    i = 0;
    while (delimiters[i] != a)
    {
        if(delimiters[i] == '\0')
            return (0);
        i++;
    }
    return (1);
}



int     end_of_cmd(char *str, char *delimiter)
{
    int     i;
    int     flag_d_q;
    int     flag_q;
    i = 0;
    flag_d_q = 0;
    flag_q = 0;
    while (str[i])
    {
		if (str[i] == '\"' && !flag_q)
		{
			if (flag_d_q == 0)
				flag_d_q = 1;
			else
				flag_d_q = 0;
		}
		if (str[i] == '\'' && !flag_d_q)
		{
			if (flag_q == 0)
				flag_q = 1;
			else
				flag_q = 0;
		}
        if (in_delimiters(str[i], delimiter) && !flag_d_q && !flag_q)
            return (i);
        i++;
    }
    return (0);
}


char	*my_strdup(const char *s1, int size)
{
	int		j;
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (size));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (j < size)
	{
		tab[j] = s1[j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

Datatoken	*ft_my_lstnew(void *content)
{
	Datatoken	*my_node;

	my_node = (Datatoken *)malloc(sizeof(Datatoken));
	if (my_node == NULL)
		return (NULL);
	my_node->cmd = content;
	my_node->type = 's';
	my_node->state = WITHOUT;
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

void	ft_my_lstadd_back(Datatoken **lst, Datatoken *new)
{
	Datatoken	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

// int main(int ac, char **av)
// {
//     printf("%d\n", end_of_cmd(av[1], av[2]));
// }