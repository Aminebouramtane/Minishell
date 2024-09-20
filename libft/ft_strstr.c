/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:42:15 by abouramt          #+#    #+#             */
/*   Updated: 2024/06/01 16:37:57 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	needle_len;
	size_t	j;

	i = 0;
	if (!haystack && needle)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i])
	{
		if (haystack[i] == *needle)
		{
			j = 0;
			while (haystack[i + j] == needle[j])
			{
				if (j == needle_len - 1)
					return ((char *)&haystack[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
