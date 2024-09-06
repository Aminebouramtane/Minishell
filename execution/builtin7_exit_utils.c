/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin7_exit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:29 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:30 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(t_parce_node *parce)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(parce->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	envi->exit_status = 2;
	ft_malloc(0, 1);
	exit(2);
}
