
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

int end_of_cmd(char *str, char *delimiter) {
    int i;
    int flag_d_q;
    int flag_q;

    i = -1;
    flag_d_q = 0;
    flag_q = 0;
    
    while (str[++i]) {
        if (str[i] == '\"' && !flag_q) {
            flag_d_q = !flag_d_q;
        }
        if (str[i] == '\'' && !flag_d_q) {
            flag_q = !flag_q;
        }
        if (in_delimiters(str[i], delimiter) && !flag_d_q && !flag_q) {
            return i;
        }
    }
    return 0;
}


char	*my_strdup(const char *s1, int size)
{
	int		j;
	char	*tab;

	if (!s1 || !*s1 || size == 0)
		return (NULL);
	tab = (char *)ft_malloc(sizeof(char) * (size + 1), 0);
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

char	*my_strdup_two(const char *s1)
{
	int		j;
	char	*tab;
	int		size;
	if (!s1 || !*s1)
		return (NULL);
	size = ft_strlen(s1);
	tab = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + 1), 0);
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
