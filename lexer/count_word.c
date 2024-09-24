/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:11:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/24 16:40:16 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

void	should_count_word(char c, char *delimiters, int *flag, int *count)
{
	if (!in_delimiters(c, delimiters) && *flag)
	{
		(*count)++;
		*flag = 0;
	}
}

void	check_if(int *flag, char c, char *delimiter)
{
	if (in_delimiters(c, delimiter))
		*flag = 1;
}

int	ft_count_word(char *s, char *delimiters)
{
	int (count), (in_quote), (i), (flag);
	count = 0;
	flag = 1;
	i = 0;
	in_quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			in_quote = !in_quote;
			if (in_quote)
				should_count_word(s[i], delimiters, &flag, &count);
			i++;
			continue ;
		}
		if (!in_quote)
		{
			should_count_word(s[i], delimiters, &flag, &count);
			check_if(&flag, s[i], delimiters);
		}
		else
			flag = 0;
		i++;
	}
	return (count);
}
