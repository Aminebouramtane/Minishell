/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:41:00 by abouramt          #+#    #+#             */
/*   Updated: 2024/08/29 20:59:15 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
	return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s2++;
		s1++;
	}
	return ((unsigned char)*s1 - (unsigned char) *s2);
}
