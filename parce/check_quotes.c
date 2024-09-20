/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:59:14 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/02 14:00:20 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *str)
{
	int	i;
	int	flag_q;
	int	flag_d_q;

	i = 0;
	flag_q = 0;
	flag_d_q = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !flag_q)
			flag_d_q = !flag_d_q;
		if (str[i] == '\'' && !flag_d_q)
			flag_q = !flag_q;
		i++;
	}
	if (flag_d_q == 1 || flag_q == 1)
		return (0);
	return (1);
}
