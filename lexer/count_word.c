/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:11:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/27 18:22:06 by abouramt         ###   ########.fr       */
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

void	check_if(int *flag, char c, char *delimiters)
{
	if (in_delimiters(c, delimiters))
		*flag = 1;
}

int	ft_count_word(char *s, char *delimiters)
{
	int		count;
	int		in_quote;
	int		i;
	int		flag;
	char	quote_char;

	count = 0;
	in_quote = 0;
	i = 0;
	flag = 1;
	quote_char = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (!in_quote)
			{
				in_quote = 1;
				quote_char = s[i];
				should_count_word(s[i], delimiters, &flag, &count);
			}
			else if (s[i] == quote_char)
				in_quote = 0;
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
