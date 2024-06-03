#include "../minishell.h"

void	run_builtin(t_parce_node *parce, t_env envi)
{
	if (ft_strncmp(parce->args[0], "echo", 4) == 0)
		ft_echo(parce);
	else if (ft_strncmp(parce->args[0], "cd", 2) == 0)
		ft_cd(parce);
	 else if (ft_strncmp(parce->args[0], "env", 3) == 0)
	 	ft_env(envi);
	else if (ft_strncmp(parce->args[0], "pwd", 3) == 0)
		ft_pwd(envi.my_env);
	// else if (ft_strncmp(args[0], "unset", 5) == 0)
	// 	ft_unset(parce);
	// else if (ft_strncmp(args[0], "export", 6) == 0)
	// 	ft_export(parce);
	// else if (ft_strncmp(args[0], "exit", 4) == 0)
	// 	ft_exit(parce);
	
}


int	check_builtins(char *command)
{
	if (command && (ft_strncmp(command, "echo", 4) == 0
		|| ft_strncmp(command, "cd", 2) == 0
		|| ft_strncmp(command, "pwd", 3) == 0
		|| ft_strncmp(command, "exit", 4) == 0
		|| ft_strncmp(command, "unset", 5) == 0
		|| ft_strncmp(command, "env", 3) == 0
		|| ft_strncmp(command, "export", 6) == 0))
		return (1);
	else
		return (0);
}


void ft_execute(t_parce_node *parce, char **env)
{	
	
	t_env envi;

	(void)env;
	envi.my_env = env;

	if (parce)
		handel_heredoc(parce);
	if (parce->args && check_builtins(parce->args[0]) == 1)
		run_builtin(parce, envi);
	// else
	// 	run_commands();
}