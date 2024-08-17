#include "../../minishell.h"

char	*my_f_strdup(const char *s1, int size)
{
	int		j;
	char	*tab;

	if (!s1 || !*s1 || size == 0)
		return (NULL);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (s1 && j < size)
	{
		tab[j] = s1[j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

void	fill_string_in_node(char *str, size_t *i, t_vars *data, char *delimiters)
{
	Datatoken	*node;
	char		*tmp;
	int			start;
	int			end;

	start = *i;
	end = *i + 1;
	while (str[end])
	{
		if (in_delimiters(str[end], delimiters))
			break;
		end++;
	}
	*i = end;
	tmp = my_strdup(str + start, end - start);
	if (data->flag)
		node = ft_my_lstnew(tmp, 's', IN_DOUBLE_COTE);
	else
		node = ft_my_lstnew(tmp, 's', GENERAL);
	ft_my_lstadd_back(&(data->ndata), node);
}
