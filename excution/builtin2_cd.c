#include "../minishell.h"

t_env	get_env_vars(char **envi)
{
	int i;
	int j;
	char *old_path;

}

void	error_cd(char *str)
{
	ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_cd(t_parce_node *parce, t_env envi)
{
	int i = 0;
	char *oldpwd;

	if (chdir(parce->args[1]) != 0)
		error_cd(parce->args[1]);

}