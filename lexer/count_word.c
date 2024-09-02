/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:11:52 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 12:18:03 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_quotes(char *s, char quote_char, int *i)
{
	split_quotes(s, quote_char, i);
	while (s[*i] && !in_delimiters(s[*i], " \t\n"))
		(*i)++;
}

static int	is_in_quotes(char *s, int *i, int *count, int *flag)
{
	char	quote_char;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		quote_char = s[*i];
		handle_quotes(s, quote_char, i);
		if (*flag)
			(*count)++;
		return (1);
	}
	return (0);
}

static int	should_count_word(char c, char *delimiters, int *flag, int *count)
{
	if (!in_delimiters(c, delimiters) && *flag)
	{
		(*count)++;
		*flag = 0;
		return (1);
	}
	return (0);
}

int	count_word(char *s, char *delimiters)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (!is_in_quotes(s, &i, &count, &flag))
		{
			should_count_word(s[i], delimiters, &flag, &count);
			if (s[i] && in_delimiters(s[i], delimiters))
				flag = 1;
		}
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}
