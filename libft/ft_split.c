/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 03:30:58 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 20:44:47 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_word(char const *s, char c)
{
	int	count;
	int	flag ;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (flag && s[i] != c)
		{
			flag = 0;
			count++;
		}
		if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

static	char	*get_word(char const *s, char c, int *index)
{
	int		i;
	int		start;
	char	*str;

	i = *index;
	while (s[i] && s[i] == c)
		i++;
	start = i;
	while (s[i] && s[i] != c)
		i++;
	str = ft_calloc((i - start) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, (i - start) + 1);
	*index = i;
	return (str);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
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
