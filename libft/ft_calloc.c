/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:01:02 by abouramt          #+#    #+#             */
/*   Updated: 2024/08/16 22:11:42 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	int		mult;

	mult = count * size;
	ptr = malloc(mult);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, mult);
	return (ptr);
}
