/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user007 <user007@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:19:08 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/06 12:10:20 by user007          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_envi->exit_status = 130;
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
