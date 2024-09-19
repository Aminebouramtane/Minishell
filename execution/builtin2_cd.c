/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:05 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/18 12:26:07 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(void)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*old_pwd;
    char	*new_pwd;

	pwd_env = find_env("PWD");
    oldpwd_env = find_env("OLDPWD");
	new_pwd = getcwd(NULL, 0);
	if (pwd_env && pwd_env->value)
        old_pwd = ft_strdup(pwd_env->value);
    else
	{
        old_pwd = NULL;
	}

	if (new_pwd == NULL)
	{
		if (pwd_env && pwd_env->value)
			new_pwd = ft_strdup(pwd_env->value);
		else
			new_pwd = ft_strdup("Unknown path");
	}
//	swapping_pwd(oldpwd_env, pwd_env);
	if (old_pwd)
    {
        if (oldpwd_env)
        {
            free(oldpwd_env->value);
            oldpwd_env->value = old_pwd;
        }
        else
        {
            char *oldpwd_str = ft_strjoin("OLDPWD=", old_pwd);
            ft_env_lstadd_back(&g_envi, ft_env_lstnew(oldpwd_str));
            free(oldpwd_str);
            free(old_pwd);
        }
    }
	else if (oldpwd_env)
    {
        // If PWD was unset, we should unset OLDPWD too
        ft_unset_a_node(oldpwd_env);
    }
	if (pwd_env)
	{
		free(pwd_env->value);
		pwd_env->value = NULL;
        pwd_env->value = new_pwd;
	}
	else
	{
		char *pwd_str = ft_strjoin("PWD=", new_pwd);
        ft_env_lstadd_back(&g_envi, ft_env_lstnew(pwd_str));
        free(pwd_str);
        free(new_pwd);
	}
}

t_env	*find_env(const char *key)
{
	t_env *env = g_envi;
	while (env && ft_strncmp(env->key, key) != 0)
		env = env->next;
	return (env);
}

void cd_home(void)
{
    t_env *home_env = find_env("HOME");

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

//void	cd_home(t_env *temp)
//{
//	while (temp && ft_strncmp(temp->key, "HOME") != 0)
//		temp = temp->next;
//	if (temp && temp->env_var != NULL && temp->value != NULL)
//		(chdir(temp->value), change_pwd());
//	else
//	{
//		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
//		g_envi->exit_status = 1;
//	}
//}

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

void	pwd_ing(void)
{
	t_env *oldpwd_env = find_env("OLDPWD");

	if (oldpwd_env && oldpwd_env->value)
    {
        if (chdir(oldpwd_env->value) == 0)
        {
            change_pwd();
            ft_pwd(); // Print the new directory
        }
        else
            perror("Minishell: cd");
    }
	else
    {
        ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
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
	//unsetted_pwd();
	if (arg_counter == 1 && temp)
		cd_home();
	else if (arg_counter == 2)
	{
		if (parce && ft_strncmp(parce->args[1], "-") == 0)
			pwd_ing();
		else if(chdir(parce->args[1]) == 0)
			change_pwd();
		else
			error_cd(parce->args[1], arg_counter);
	}
	else
		error_cd(parce->args[1], arg_counter);
}
