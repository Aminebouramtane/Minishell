/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:11:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 12:17:45 by abouramt         ###   ########.fr       */
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

int	ft_process_quote(char c, int *in_quote, char *quote_char)
{
	if (is_quote(c))
	{
		if (!*in_quote)
		{
			*in_quote = 1;
			*quote_char = c;
		}
		else if (c == *quote_char)
			*in_quote = 0;
		return (1);
	}
	return (0);
}

void	ft_process_word(char c, char *delimiters, int *flag, int *count, int in_quote)
{
	if (!in_quote)
	{
		should_count_word(c, delimiters, flag, count);
		check_if(flag, c, delimiters);
	}
	else
		*flag = 0;
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
		if (ft_process_quote(s[i], &in_quote, &quote_char))
		{
			should_count_word(s[i], delimiters, &flag, &count);
			i++;
			continue ;
		}
		ft_process_word(s[i], delimiters, &flag, &count, in_quote);
		i++;
	}
	return (count);
}

