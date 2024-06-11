#include "../minishell.h"


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

void	change_pwd(t_env *temp)
{
	t_env	*temp2;
	t_env	*temp3;
	char	*str;

	temp2 = temp;
	temp3 = temp;
	str = NULL;
	while (temp3 && ft_strncmp(temp3->env_var, "PWD=") != 0)
		temp3 = temp3->next;
	if (temp3)
		str = ft_my_strjoin(str, temp3->env_var + 4);
	while (temp && ft_strncmp(temp->env_var, "OLDPWD=") != 0)
		temp = temp->next;
	temp->env_var = ft_strjoin("OLDPWD=", str);
	while (temp2 && ft_strncmp(temp2->env_var, "PWD=") != 0)
		temp2 = temp2->next;
	if (!temp2)
		return ;
	temp2->env_var = ft_strjoin("PWD=", getcwd(NULL, 0));

}

void	ft_cd(t_parce_node *parce)
{
	t_env	*temp;
	int		arg_counter;


	arg_counter = 0;
	temp = envi;
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (arg_counter >= 2)
	{
		if (chdir(parce->args[1]) != 0)
			error_cd(parce->args[1], arg_counter);
		else
			change_pwd(temp);
	}
	else
	{
		while (temp && ft_strncmp(temp->env_var, "HOME") != 0)
			temp = temp->next;
		if (temp && temp->env_var != NULL)
		{
			chdir(temp->env_var + 5);
			change_pwd(temp);
		}
		else
			ft_putstr_fd("Minishell: cd: HOME not set\n", 1);
	}
}
