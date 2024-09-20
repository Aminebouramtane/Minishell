/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:44:01 by abouramt          #+#    #+#             */
/*   Updated: 2024/09/19 15:47:05 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_mystrjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	len;

	ptr = NULL;
	if (!s1 || s1 == NULL)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	if (s1)
		while (s1[++i])
			ptr[i] = s1[i];
	else
		i = 0;
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return (ptr);
}

void	error_cd(char *str, int a_counter)
{
	if (a_counter == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		if (g_envi)
			g_envi->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		if (g_envi)
			g_envi->exit_status = 1;
	}
}

t_env	*find_env(const char *key)
{
	t_env	*env;

	env = g_envi;
	while (env && ft_strncmp(env->key, key) != 0)
		env = env->next;
	return (env);
}

void	change_pwd(void)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*old_pwd;
	char	*new_pwd;

	pwd_env = find_env("PWD");
	oldpwd_env = find_env("OLDPWD");
	old_pwd = NULL;
	if (pwd_env && pwd_env->value)
		old_pwd = ft_strdup(pwd_env->value);
	new_pwd = get_new_pwd(pwd_env);
	if (old_pwd)
		update_oldpwd(oldpwd_env, old_pwd);
	else if (oldpwd_env)
		ft_unset_a_node(oldpwd_env);
	update_pwd(pwd_env, new_pwd);
}

void	pwd_ing(void)
{
	t_env	*oldpwd_env;

	oldpwd_env = find_env("OLDPWD");
	if (oldpwd_env && oldpwd_env->value)
	{
		if (chdir(oldpwd_env->value) == 0)
		{
			change_pwd();
			ft_pwd();
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
