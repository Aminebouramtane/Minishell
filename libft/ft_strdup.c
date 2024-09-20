/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:30:09 by abouramt          #+#    #+#             */
/*   Updated: 2024/06/12 18:13:27 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*tab;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tab[j] = s1[j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
