/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:05 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/17 22:02:11 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(void)
{
	t_env	*old_pwd_env;
	t_env	*pwd_env;
	char	*buffer;

	old_pwd_env = g_envi;
	pwd_env = g_envi;
	while (pwd_env && ft_strncmp(pwd_env->key, "PWD") != 0)
		pwd_env = pwd_env->next;
	while (old_pwd_env && ft_strncmp(old_pwd_env->key, "OLDPWD") != 0)
		old_pwd_env = old_pwd_env->next;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		if (pwd_env && pwd_env->value)
			buffer = ft_strdup(pwd_env->value);
		else
			buffer = ft_strdup("Unknown path");
	}
	swapping_pwd(old_pwd_env, pwd_env);
	if (pwd_env)
	{
		if (pwd_env->value)
		{
			free(pwd_env->value);
			pwd_env->value = NULL;
		}
		pwd_env->value = ft_strdup(buffer);
	}
	free(buffer);
}

void	cd_home(t_env *temp)
{
	while (temp && ft_strncmp(temp->key, "HOME") != 0)
		temp = temp->next;
	if (temp && temp->env_var != NULL && temp->value != NULL)
		(chdir(temp->value), change_pwd());
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		g_envi->exit_status = 1;
	}
}

void	unsetted_pwd(void)
{
	t_env	*temp1;
	char	*pwd;
	char	*current;

	temp1 = g_envi;
	current = getcwd(NULL, 0);
	if (current == NULL)
	{
		while (temp1 && ft_strncmp(temp1->key, "PWD") != 0)
			temp1 = temp1->next;
		if (temp1 && temp1->value)
			current = ft_strdup(temp1->value);
		else
			current = ft_strdup("Unknown path");
	}
	pwd = ft_strjoin_path("PWD=", current);
	free(current);
	temp1 = g_envi;
	while (temp1 && ft_strncmp(temp1->key, "PWD") != 0)
		temp1 = temp1->next;
	if (temp1 != NULL)
	{
		ft_unset_a_node(temp1);
	}
	ft_env_lstadd_back(&g_envi, ft_env_lstnew(pwd));
	free(pwd);
}

void	pwd_ing(t_env *temp)
{
	while (temp && ft_strncmp(temp->key, "OLDPWD") != 0)
		temp = temp->next;
	if (temp)
	{
		chdir(temp->value);
		change_pwd();
	}
}

void	ft_cd(t_parce_node *parce)
{
	t_env	*temp;
	int		arg_counter;

	arg_counter = 0;
	temp = g_envi;
	unsetted_pwd();
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (arg_counter == 2)
	{
		if (parce && ft_strncmp(parce->args[1], "-") == 0)
			pwd_ing(temp);
		if (chdir(parce->args[1]) != 0)
			error_cd(parce->args[1], arg_counter);
		else
			change_pwd();
	}
	else if (arg_counter > 2)
		error_cd(parce->args[1], arg_counter);
	else if (arg_counter == 1 && temp)
		cd_home(temp);
}
