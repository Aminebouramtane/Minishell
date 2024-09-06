/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:19:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 12:35:12 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	envi->exit_status = 130;
}

void	ft_handler2(void)
{
	write(1, "\n", 1);
}

void	ft_handler3(void)
{
	exit(0);
	write(1, "exit\n", 1);
}
