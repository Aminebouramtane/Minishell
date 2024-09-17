/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:05 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/15 19:06:09 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(void)
{
	t_env	*temp2;
	t_env	*temp3;
	char	*buffer;

	temp2 = g_envi;
	temp3 = g_envi;
	while (temp3 && ft_strncmp(temp3->key, "PWD") != 0)
		temp3 = temp3->next;
	while (temp2 && ft_strncmp(temp2->key, "OLDPWD") != 0)
		temp2 = temp2->next;
	buffer = getcwd(NULL, 0);
	swapping_pwd(temp2, temp3);
	if (temp3)
	{
		if (temp3 && temp3->value)
		{
			free(temp3->value);
			temp3->value = NULL;
			temp3->value = ft_strdup(buffer);
		}
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
	pwd = ft_strjoin_path("PWD=", current);
	free(current);
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
