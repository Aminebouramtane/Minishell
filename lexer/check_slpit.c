/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_slpit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:32:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 12:38:14 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_non_quoted_string(char *src, int *i, char *delimiters)
{
	while (src[*i] && !in_delimiters(src[*i], delimiters))
		(*i)++;
}

static char	*get_word(char *dst, char *src, char *delimiters, int *index)
{
	int	i;
	int	start;
	int	len;

	i = *index;
	i = skip_delimiters(src, delimiters, i);
	start = i;
	while (src[i])
	{
		if (src[i] == '\"' || src[i] == '\'')
			split_quotes(src, src[i], &i);
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

static char	**fill_array(char **dst, char *src,
	char *delimiters, int number_word)
{
	int	i;
	int	index_word;

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

char	**split_lexer(char *s, char *delimiters)
{
	char	**dst;
	int		count;

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
