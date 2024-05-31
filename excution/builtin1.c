#include "../minishell.h"

void	run_builtin(t_parce_node *parce)
{
	if (ft_strncmp(parce->args[0], "echo", 4) == 0)
		ft_echo(parce);
	// else if (ft_strncmp(args[0], "cd", 2) == 0)
	// 	ft_cd(parce);
	// else if (ft_strncmp(args[0], "pwd", 3) == 0)
	// 	ft_pwd(parce);
	// else if (ft_strncmp(args[0], "unset", 5) == 0)
	// 	ft_unset(parce);
	// else if (ft_strncmp(args[0], "export", 6) == 0)
	// 	ft_export(parce);
	// else if (ft_strncmp(args[0], "exit", 4) == 0)
	// 	ft_exit(parce);
	// else if (ft_strncmp(args[0], "env", 3) == 0)
	// 	ft_env(parce);
	
}

void	echo_without_flag(t_parce_node *parce)
{
	int i;

	i = 1;
	while (parce->args[i] != NULL)
	{
		ft_putstr_fd(parce->args[i], 1);
		if (parce->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	echo_print(t_parce_node *parce, int i)
{
	while (parce->args[i] != NULL)
		{
			ft_putstr_fd(parce->args[i], 1);
			if (parce->args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
}


void	ft_echo(t_parce_node *parce)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	if (parce->args[i] == NULL)
		ft_putstr_fd("\n", 1);
	else if (parce->args[1][j] == '-')
	{
		j++;
		while (parce->args[1][j] != '\0' && (parce->args[1][j] == 'n'))
			j++;
		if (parce->args[i][j] == '\0')
		{
			i = 2;
			echo_print(parce, i);
			printf("hehe");
		}
		else
		{
			i = 1;
			echo_print(parce, i);
			ft_putstr_fd("\n", 1);
		}	
	}
	else
		echo_without_flag(parce);
	
}
