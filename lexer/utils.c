
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

	if (!s1 || !*s1 || size == 0)
		return (NULL);
	tab = (char *)ft_malloc(sizeof(char) * (size), 0);
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

char	*my_strdup_two(const char *s1)
{
	int		j;
	char	*tab;
	int		size;
	if (!s1 || !*s1)
		return (NULL);
	size = ft_strlen(s1);
	tab = (char *)ft_malloc(sizeof(char) * ft_strlen(s1), 0);
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

Datatoken	*ft_my_lstnew(void *content, char type, char state)
{
	Datatoken	*my_node;

	my_node = (Datatoken *)ft_malloc(sizeof(Datatoken), 0);
	if (my_node == NULL)
		return (NULL);
	my_node->cmd = content;
	my_node->type = type;
	my_node->state = state;
	my_node->prev = NULL;
	my_node->next = NULL;
	return (my_node);
}

Datatoken	*ft_my_lstlast(Datatoken *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_my_lstadd_back(Datatoken **lst, Datatoken *new)
{
	Datatoken	*last;
	Datatoken	*prev;
	Datatoken	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	prev = ft_my_lstlast(tmp);
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	last->prev = prev;
}

void	ft_my_lstclear(Datatoken **lst)
{
	Datatoken	*c;
	Datatoken	*n;

	if (lst && *lst)
	{
		c = *lst;
		while (c)
		{
			n = c->next;
			free(c->cmd);
			free(c);
			c = n;
		}
		*lst = NULL;
	}
}