#include "../minishell.h"

t_env	*get_env_vars(char **env_vars)
{
	t_env *envi;
	int i;

	i = 0;
	envi = NULL;
	while (env_vars && env_vars[i])
	{
		ft_env_lstadd_back(&envi, ft_env_lstnew(env_vars[i]));
		i++;
	}
	return (envi);
}

// void	change_pwd()
// {

// }

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

void	ft_cd(t_parce_node *parce, t_env *envi)
{
	t_env	*temp;
	int		i;
	int		arg_counter;
	char	path[4026];

	i = 0;
	arg_counter = 0;
	temp = envi;
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (arg_counter >= 2)
	{
		if (chdir(parce->args[1]) != 0)
			error_cd(parce->args[1], arg_counter);
		else
		{
			while (temp && ft_strncmp(temp->env_var, "PWD=", 4) != 0)
				temp = temp->next;
			if (!temp)
				return ;
			printf("========================%s\n", temp->env_var);
			printf("hna\n");
			temp->env_var = ft_strjoin("PWD=", getcwd(path, sizeof(path)));
			// temp->env_var = getcwd(path, sizeof(path));
			printf("========================%s\n", temp->env_var);
			// exit(1);
			printf("%s hehe\n", temp->env_var);
		}	
	}
	else
	{
		while (temp && ft_strncmp(temp->env_var, "HOME", 4) != 0)
			temp = temp->next;
		printf("%s\n", temp->env_var);
		chdir(temp->env_var + 5);

	}
}
