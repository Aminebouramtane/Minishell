
#include "../libft/libft.h"

int	ft_strchr2(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return (1);
}

static	int	count_word(char const *s, char *c)
{
	int	count;
	int	flag ;
	int	i;
    int is_quotes;

    is_quotes = 1;
	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
        if (s[i] == '\"' || s[i] == '\'')
        {
            if (is_quotes)
                is_quotes = 0;
            else
                is_quotes = 1;
        }
		if (is_quotes && flag && !ft_strchr2(c, s[i]))
		{
			flag = 0;
			count++;
		}
		if (ft_strchr2(c, s[i]))
			flag = 1;
		i++;
	}
	return (count);
}

void    check_quote(char c, int *index)
{
    if (c == '\"' || c == '\'')
    {
        if (!*index)
            *index = 1;
        else
            *index = 0;
    }
}

static	char	*get_word(char const *s, char *c, int *index)
{
	int		i;
	int		start;
	char	*str;
    int     is_quotes;

    is_quotes = 0;
	i = *index;

    while (s[i] && ft_strchr2(c, s[i]))
        i++;
    start = i;
    check_quote(s[i], &is_quotes);
    if (is_quotes)
    {
        is_quotes = 0;
        i++;
        while (s[i] && !is_quotes)
        {
            check_quote(s[i], &is_quotes);
            if (is_quotes)
            {
                is_quotes = 0;
                break;
            }
            i++;
        }
    }
    while (s[i] && !ft_strchr2(c, s[i]) && !is_quotes)
    {
        i++;
        check_quote(s[i], &is_quotes);
    }
    str = ft_calloc((i - start) + 1, sizeof(char));
    if (!str)
        return (NULL);
    ft_strlcpy(str, s + start, (i - start) + 1);
	*index = i;
	return (str);
}

static	void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**split_lexer(char const *s, char *c)
{
	char	**str;
	int		index;
	int		i;

	if (!s)
		return (NULL);
	str = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count_word(s, c))
	{
		str[i] = get_word(s, c, &index);
		if (!str[i])
		{
			ft_free(str);
			return (NULL);
		}
		i++;
	}
	return (str);
}

// int main(int ac, char **av)
// {
// 	int i;

// 	i = 0;
// 	(void)ac;
// 	char **str = split_lexer( av[1], " \t\n\r\f\v");
// 	while (str[i])
// 	{
// 		printf("%s\n", str[i]);
// 		i++;
// 	}
// }