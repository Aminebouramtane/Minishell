/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:29:52 by yimizare          #+#    #+#             */
/*   Updated: 2024/09/19 15:45:25 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_in_files(t_parce_node *temp, char **envp)
{
	int	flag;

	flag = open_in_files_redirp(temp->file, 0);
	if (flag == 1)
	{
		file_error(temp->file, envp);
		return (flag);
	}
	return (0);
}

int	handle_out_files(t_parce_node *temp, char **envp)
{
	int	flag;

	flag = open_out_files_redirp(temp->file, 1);
	if (flag == 1)
	{
		file_error(temp->file, envp);
		return (flag);
	}
	return (0);
}

int	handle_append_files(t_parce_node *temp, char **envp)
{
	int	flag;

	flag = open_files_appendp(temp->file, 1);
	if (flag == 1)
	{
		file_error(temp->file, envp);
		return (flag);
	}
	return (0);
}
