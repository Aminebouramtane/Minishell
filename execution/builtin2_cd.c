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
		ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	}
}

void	change_pwd()
{
	t_env	*temp2;
	t_env	*temp3;
	char	*buffer;

	temp2 = envi;
	temp3 = envi;
	while (temp3 && ft_strncmp(temp3->key, "PWD") != 0)
		temp3 = temp3->next;
	while (temp2 && ft_strncmp(temp2->key, "OLDPWD") != 0)
		temp2 = temp2->next;
	temp2->value = temp3->value;
	buffer = getcwd(NULL, 0);
	temp3->value = ft_strdup(buffer);
	free(buffer);
}

void	ft_cd(t_parce_node *parce)
{
	t_env	*temp;
	int		arg_counter;

	arg_counter = 0;
	temp = envi;
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (arg_counter == 2)
	{
		if (parce && ft_strncmp(parce->args[1], "-") == 0)
			{
				while (temp && ft_strncmp(temp->key, "OLDPWD") != 0)
					temp = temp->next;
				chdir(temp->value);
				change_pwd();
			}
		else if (chdir(parce->args[1]) != 0)
			error_cd(parce->args[1], arg_counter);
		else
			change_pwd();
	}
	else if (arg_counter > 2)
		error_cd(parce->args[1], arg_counter);
	else if (arg_counter == 1)
	{
		while (temp && ft_strncmp(temp->key, "HOME") != 0)
			temp = temp->next;
		if (temp && temp->env_var != NULL && temp->value != NULL)
			(chdir(temp->value), change_pwd());
		else
			ft_putstr_fd("Minishell: cd: HOME not set\n", 1);
	}
}
