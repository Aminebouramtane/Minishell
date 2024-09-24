/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:11 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/24 16:46:22 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*path;
	t_env	*pwd_env;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		pwd_env = g_envi;
		while (pwd_env && pwd_env->key && ft_strncmp(pwd_env->key, "PWD") != 0)
			pwd_env = pwd_env->next;
		if (pwd_env && pwd_env->value)
			ft_putstr_fd(pwd_env->value, 1);
		else
			ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd(path, 1);
		free(path);
	}
	ft_putstr_fd("\n", 1);
}
