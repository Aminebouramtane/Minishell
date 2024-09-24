/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:11:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/22 16:43:30 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	handle_quotes(char *s, char quote_char, int *i)
// {
// 	split_quotes(s, quote_char, i);
// 	while (s[*i] && !in_delimiters(s[*i], " \t\n"))
// 		(*i)++;
// }

// static int	is_in_quotes(char *s, int *i, int *count, int *flag)
// {
// 	char	quote_char;

// 	if (s[*i] == '\"' || s[*i] == '\'')
// 	{
// 		quote_char = s[*i];
// 		handle_quotes(s, quote_char, i);
// 		if (*flag)
// 			(*count)++;
// 		return (1);
// 	}
// 	return (0);
// }

// static int	should_count_word(char c, char *delimiters, int *flag, int *count)
// {
// 	if (!in_delimiters(c, delimiters) && *flag)
// 	{
// 		(*count)++;
// 		*flag = 0;
// 		return (1);
// 	}
// 	return (0);
// }

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

int	ft_count_word(char *s, char *delimiters)
{
	int	count;
	int	flag;
	int	i;
	int	in_quote;

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
			continue;
		}
		if (!in_quote)
		{
			should_count_word(s[i], delimiters, &flag, &count);
			if (in_delimiters(s[i], delimiters))
				flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	return (count);
}
