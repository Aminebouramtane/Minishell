/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:57:54 by abouramt          #+#    #+#             */
/*   Updated: 2024/05/23 18:48:41 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int		i;
	int		flag_q;
	int		flag_d_q;

	i = 0;
	flag_q = 0;
	flag_d_q = 0;
	
	while (str[i])
	{
		if (str[i] == '\"' && !flag_q)
		{
			if (flag_d_q == 0)
				flag_d_q = 1;
			else
				flag_d_q = 0;
		}
		if (str[i] == '\'' && !flag_d_q)
		{
			if (flag_q == 0)
				flag_q = 1;
			else
				flag_q = 0;
		}
		i++;
	}
	if (flag_d_q == 1 || flag_q == 1)
		return (0);
	return (1);
}
