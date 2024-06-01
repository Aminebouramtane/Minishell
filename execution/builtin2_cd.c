#include "../minishell.h"

// t_env	get_env_vars(char **envi)
// {
// 	int i;
// 	int j;
// 	char *old_path;

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
		ft_putstr_fd("minishell: cd: too many arguments", 2);
	}
}

void	ft_cd(t_parce_node *parce)
{
	int i;
	int arg_counter;

	i = 0;
	arg_counter = 0;
	while (parce->args[arg_counter] != NULL)
		arg_counter++;
	if (chdir(parce->args[1]) != 0 || arg_counter != 2)
		error_cd(parce->args[1], arg_counter);
}
