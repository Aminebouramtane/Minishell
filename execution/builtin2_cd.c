/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:05 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/19 15:35:48 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_env *oldpwd_env, char *old_pwd)
{
	char	*oldpwd_str;

	if (oldpwd_env)
	{
		free(oldpwd_env->value);
		oldpwd_env->value = old_pwd;
	}
	else if (old_pwd)
	{
		oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
		ft_env_lstadd_back(&g_envi, ft_env_lstnew(oldpwd_str));
		free(oldpwd_str);
		free(old_pwd);
	}
}

void	update_pwd(t_env *pwd_env, char *new_pwd)
{
	char	*pwd_str;

	if (pwd_env)
	{
		free(pwd_env->value);
		pwd_env->value = new_pwd;
	}
	else
	{
		pwd_str = ft_strjoin("PWD=", new_pwd);
		ft_env_lstadd_back(&g_envi, ft_env_lstnew(pwd_str));
		free(pwd_str);
		free(new_pwd);
	}
}

char	*get_new_pwd(t_env *pwd_env)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		if (pwd_env && pwd_env->value)
			new_pwd = ft_strdup(pwd_env->value);
		else
			new_pwd = ft_strdup("Unknown path");
	}
	return (new_pwd);
}

void	cd_home(void)
{
	t_env	*home_env;

	home_env = find_env("HOME");
	if (home_env && home_env->value)
	{
		if (chdir(home_env->value) == 0)
			change_pwd();
		else
			perror("Minishell: cd");
	}
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		g_envi->exit_status = 1;
	}
}

void	ft_cd(t_parce_node *parce)
{
	t_env	*temp;
	int		arg_counter;

	arg_counter = 0;
	temp = g_envi;
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (arg_counter == 1 && temp)
		cd_home();
	else if (arg_counter == 2)
	{
		if (parce && ft_strncmp(parce->args[1], "-") == 0)
			pwd_ing();
		else if (chdir(parce->args[1]) == 0)
			change_pwd();
		else
			error_cd(parce->args[1], arg_counter);
	}
	else
		error_cd(parce->args[1], arg_counter);
}
