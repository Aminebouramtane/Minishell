/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:28:11 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 12:31:34 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	split_quotes(char *target, char delimiter, int *index)
{
	int	i;

	i = *index;
	i++;
	while (target[i])
	{
		if (target[i] == delimiter)
		{
			i++;
			break ;
		}
		i++;
	}
	*index = i;
}

int	skip_delimiters(char *s, char *delimiters, int i)
{
	while (s[i] && in_delimiters(s[i], delimiters))
		i++;
	return (i);
}
