/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:54:10 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/29 12:07:53 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = (char *)malloc(len + 1);
	if (ptr == 0)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && i < ft_strlen(s))
	{
		ptr[j] = s[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_my_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (my_strdup_two(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = ft_malloc(len + 1, 0);
	if (ptr == 0)
		return (NULL);
	i = start;
	j = 0;
	while (j < len && i < ft_strlen(s))
	{
		ptr[j] = s[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
