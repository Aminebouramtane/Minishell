/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin7_exit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:29 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/12 20:38:58 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(t_parce_node *parce, char **envp)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(parce->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_envi->exit_status = 2;
	ft_free(envp);
	ft_env_lstclear(g_envi);
	ft_malloc(0, 1);
	exit(2);
}
