#include "../minishell.h"


void	*ft_ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	int		mult;

	mult = count * size;
	ptr = ft_malloc(mult, 0);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, mult);
	return (ptr);
}

void split_quotes(char *target, char delimiter, int *index)
{
	int i;

	i = *index;
	i++;
	while (target[i])
	{
		if (target[i] == delimiter)
		{
			i++;
			break;
		}
		i++;
	}
	*index = i;
}

static int count_word(char *s, char *delimiters)
{
	int count;
	int flag;
	int i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			split_quotes(s, '\"', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n"))
				i++;
			if (flag)
				count++;
		}
		else if (s[i] && s[i] == '\'')
		{
			split_quotes(s, '\'', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n"))
				i++;
			if (flag)
				count++;
		}
 		if (s[i] && !in_delimiters(s[i], delimiters) && flag)
 		{
 			count++;
			flag = 0;
		}
		if (s[i] && in_delimiters(s[i], delimiters))
		flag = 1;
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

int skip_delimiters(char *s, char *delimiters, int i)
{
	while (s[i] && in_delimiters(s[i], delimiters))
		i++;
	return i;
}

void process_quoted_string(char *src, int *i, char quote)
{
	split_quotes(src, quote, i);
}
void process_non_quoted_string(char *src, int *i, char *delimiters)
{
	while (src[*i] && !in_delimiters(src[*i], delimiters))
	{
		(*i)++;
	}
}
static char *get_word(char *dst, char *src, char *delimiters, int *index)
{
	int i;
	int start;
	int len;

	i = *index;
	i = skip_delimiters(src, delimiters, i);
	start = i;
	while (src[i])
	{
		if (src[i] == '\"' || src[i] == '\'')
		{
			process_quoted_string(src, &i, src[i]);
		}
		else if (src[i] && !in_delimiters(src[i], "\'\" \n\t"))
			process_non_quoted_string(src, &i, " \t\n\'\"");
		else
			break ;
	}
	
	len = (i - start) + 1;
	dst = ft_ft_calloc(len, sizeof(char));
	ft_strlcpy(dst, src + start, len);
	*index = i;
	return (dst);
}

static char **fill_array(char **dst, char *src, char *delimiters, int number_word)
{
	int i;
	int index_word;

	index_word = 0;
	i = 0;
	while (i < number_word)
	{
		dst[i] = get_word(dst[i], src, delimiters, &index_word);
		if (!dst[i])
			ft_free(dst);
		i++;
	}
	return (dst);
}

char **split_lexer(char *s, char *delimiters)
{
	char **dst;
	int count;

	if (!s || !delimiters)
		return (NULL);
	count = 0;
	count = count_word(s, delimiters);
	dst = ft_ft_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	dst = fill_array(dst, s, delimiters, count);
	return (dst);
}
